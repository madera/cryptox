// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2018                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#pragma once
#include "../detail/openssl.hxx"
#include "../detail/exceptions.hxx"
#include <boost/noncopyable.hpp>

namespace cryptox {

	template <
		class Algorithm,
		openssl::cipher_init_fx_t   InitFx,
		openssl::cipher_update_fx_t UpdateFx,
		openssl::cipher_final_fx_t  FinalFx
	>
	class evp_cipher_context : boost::noncopyable {
		EVP_CIPHER_CTX _context;
	public:
		template <class KeyInputIterator, class IVInputIterator>
		evp_cipher_context(KeyInputIterator key_first, KeyInputIterator key_last,
		                    IVInputIterator  iv_first,  IVInputIterator  iv_last) {

			std::uint8_t key[EVP_MAX_KEY_LENGTH];
			std::copy(key_first, key_last, key);

			std::uint8_t iv[EVP_MAX_IV_LENGTH];
			std::copy(iv_first, iv_last, iv);

			EVP_CIPHER_CTX_init(&_context);
			if (InitFx(&_context, Algorithm::cipher(), 0, key, iv) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		~evp_cipher_context() {
			EVP_CIPHER_CTX_cleanup(&_context);
		}

		void reset() {
			if (InitFx(&_context, 0, 0, 0, 0) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		template <class InputIterator, class OutputIterator>
		OutputIterator update(InputIterator input_first, InputIterator input_last, OutputIterator output_first) {
			InputIterator input_itr = input_first;
			OutputIterator output_itr = output_first;

			while (input_itr != input_last) {
				std::uint8_t  input_buffer[1024];
				std::uint8_t output_buffer[1024 + EVP_MAX_BLOCK_LENGTH];

				size_t input_buffer_size = 0;
				int   output_buffer_size = 0;

				while (input_buffer_size < sizeof(input_buffer) && input_itr != input_last)
					input_buffer[input_buffer_size++] = *input_itr++;

				if (UpdateFx(&_context, output_buffer, &output_buffer_size,
				             input_buffer, input_buffer_size) != 1)
					return output_first;

				output_itr = std::copy(output_buffer, output_buffer + output_buffer_size, output_itr);
			}

			return output_itr;
		}

		template <class OutputIterator>
		OutputIterator finalize(OutputIterator output_first) {
			std::uint8_t buffer[2*EVP_MAX_BLOCK_LENGTH];

			int written;
			if (FinalFx(&_context, buffer, &written) != 1)
				written = 0;

			return std::copy(buffer, buffer + written, output_first);
		}

	};
}

namespace cryptox {

	template <
		class Algorithm,
		openssl::cipher_init_fx_t   InitFx,
		openssl::cipher_update_fx_t UpdateFx,
		openssl::cipher_final_fx_t  FinalFx
	>
	struct basic_endec : public evp_cipher_context<Algorithm, InitFx, UpdateFx, FinalFx> {
		typedef evp_cipher_context<Algorithm, InitFx, UpdateFx, FinalFx> base_type;

		template <class KeyInputIterator, class IVInputIterator>
		basic_endec(KeyInputIterator key_first, KeyInputIterator key_last,
		             IVInputIterator  iv_first,  IVInputIterator  iv_last)
		 : base_type(key_first, key_last, iv_first, iv_last) {
			// TODO: Use easy PBKDF2 for users.
			// uint8_t garbled_key[32];
			// PKCS5_PBKDF2_HMAC_SHA1(
			// 	(const char*)&_key[0],  _key.size(),
			// 	&_salt[0], _salt.size(),
			// 	key_rounds,
			// 	EVP_CIPHER_key_length(Cipher()),
			// 	garbled_key
			// );
		}

		template <class InputIterator, class OutputIterator>
		OutputIterator operator()(InputIterator input_first, InputIterator input_last, OutputIterator output_first) {
			this->reset();
			OutputIterator itr = this->update(input_first, input_last, output_first);
			return this->finalize(itr);
		}
	};

}
