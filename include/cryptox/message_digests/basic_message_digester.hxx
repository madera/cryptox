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
		openssl::message_digest_init_fx_t   InitFx   = EVP_DigestInit_ex,
		openssl::message_digest_update_fx_t UpdateFx = EVP_DigestUpdate,
		openssl::message_digest_final_fx_t  FinalFx  = EVP_DigestFinal_ex
	>
	class evp_message_digest_context : boost::noncopyable {
		typedef evp_message_digest_context this_type;
		EVP_MD_CTX _context;
	public:
		evp_message_digest_context() {
			EVP_MD_CTX_init(&_context);

			if (InitFx(&_context, Algorithm::digest(), NULL) == 0)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		~evp_message_digest_context() {
			EVP_MD_CTX_cleanup(&_context);
		}

		void reset() {
			if (InitFx(&_context, 0, 0) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		template <class InputIterator>
		InputIterator update(InputIterator input_first, InputIterator input_last) {
			InputIterator input_itr = input_first;

			while (input_itr != input_last) {
				std::uint8_t  input_buffer[1024];
				size_t input_buffer_size = 0;

				while (input_buffer_size < sizeof(input_buffer) && input_itr != input_last)
					input_buffer[input_buffer_size++] = *input_itr++;

				if (UpdateFx(&_context, input_buffer, input_buffer_size) != 1)
					BOOST_THROW_EXCEPTION(evp_error());
			}

			return input_itr;
		}

		template <class OutputIterator>
		OutputIterator finalize(OutputIterator output_first) {
			std::uint8_t buffer[2*EVP_MAX_BLOCK_LENGTH];

			unsigned int written;
			if (FinalFx(&_context, buffer, &written) != 1)
				written = 0;

			return std::copy(buffer, buffer + written, output_first);
		}

	};
}

namespace cryptox {

	template <class Algorithm>
	struct basic_message_digester : public evp_message_digest_context<Algorithm> {
		template <class InputIterator, class OutputIterator>
		OutputIterator operator()(InputIterator input_first, InputIterator input_last, OutputIterator output_first) {
			this->reset();
			this->update(input_first, input_last);
			return this->finalize(output_first);
		}
	};

}
