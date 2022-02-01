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
		EVP_CIPHER_CTX* _context;

		std::size_t _padding = Algorithm::block_size();

		std::size_t _total_input = 0;
		std::size_t _total_output = 0;

	public:
		std::size_t total_input() const {
			return _total_input;
		}

		std::size_t total_output() const {
			return _total_output;
		}

	public:
		template <class KeyInput, class IVInput>
		evp_cipher_context(KeyInput key_first, KeyInput key_last,
		                    IVInput  iv_first,  IVInput  iv_last)
		 : _total_input(0),
		   _total_output(0) {
			std::uint8_t key[EVP_MAX_KEY_LENGTH];
			std::copy(key_first, key_last, key);

			std::uint8_t iv[EVP_MAX_IV_LENGTH];
			std::copy(iv_first, iv_last, iv);

			_context = EVP_CIPHER_CTX_new();

			const EVP_CIPHER* cipher = Algorithm::cipher();
			if (InitFx(_context, cipher, 0, key, iv) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		~evp_cipher_context() {
			EVP_CIPHER_CTX_free(_context);
		}

		void reset() {
			if (InitFx(_context, 0, 0, 0, 0) != 1)
				BOOST_THROW_EXCEPTION(evp_error(/* TODO */));

			padding(_padding);

			_total_input = 0;
			_total_output = 0;
		}

		template <class Input, class Output>
		Output update(Input first, Input last, Output d_first) {
			Input   itr = first;
			Output oitr = d_first;

			while (itr != last) {
				std::uint8_t input[1024];
				std::uint8_t output[1024 + EVP_MAX_BLOCK_LENGTH];

				size_t i_sz = 0;
				int    o_sz = 0;

				while (i_sz < sizeof(input) && itr != last)
					input[i_sz++] = *itr++;

				if (UpdateFx(_context, output, &o_sz, input, i_sz) != 1)
					return d_first;

				oitr = std::copy(output, output + o_sz, oitr);

				_total_input += i_sz;
				_total_output += o_sz;
			}

			return oitr;
		}

		template <class Output>
		Output finalize(Output first) {
			std::uint8_t buffer[2*EVP_MAX_BLOCK_LENGTH];

			int written;
			if (FinalFx(_context, buffer, &written) != 1)
				written = 0;

			_total_output += written;

			return std::copy(buffer, buffer + written, first);
		}

		std::size_t padding() const {
			return _padding;
		}

		void padding(const std::size_t value) {
			_padding = value;
			EVP_CIPHER_CTX_set_padding(_context, _padding);
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
	struct basic_endec : public evp_cipher_context<
		Algorithm,
		InitFx,
		UpdateFx,
		FinalFx
	> {
		typedef evp_cipher_context<
			Algorithm,
			InitFx,
			UpdateFx,
			FinalFx
		> base_type;

		typedef Algorithm algorithm_type;

		template <class KeyInput, class IVInput>
		basic_endec(KeyInput key_first, KeyInput key_last,
		             IVInput  iv_first,  IVInput  iv_last)
		 : base_type(key_first, key_last, iv_first, iv_last) {
		}

		template <class Input, class Output>
		Output operator()(Input first, Input last, Output d_first) {
			this->reset();
			Output itr = this->update(first, last, d_first);
			return this->finalize(itr);
		}
	};

}
