// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2017                          ]
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
#include <boost/throw_exception.hpp>

namespace cryptox {

	template <
		class Algorithm,
		openssl::message_digest_init_fx_t   InitFx,
		openssl::message_digest_update_fx_t UpdateFx,
		openssl::message_digest_final_fx_t  FinalFx
	>
	class evp_message_digest_context : boost::noncopyable {
		typedef evp_message_digest_context this_type;
		EVP_MD_CTX* _context;
	public:
		evp_message_digest_context() {
			_context = EVP_MD_CTX_new();

			if (InitFx(_context, Algorithm::digest(), NULL) == 0)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		~evp_message_digest_context() {
			EVP_MD_CTX_free(_context);
		}

		void reset() {
			if (InitFx(_context, 0, 0) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
		}

		template <class Input>
		Input update(Input first, Input last) {
			Input itr = first;

			while (itr != last) {
				std::uint8_t buffer[1024];
				size_t size = 0;

				const std::size_t element_size = sizeof(*itr);
				while (size + element_size < sizeof(buffer) && itr != last) {
					const std::uint8_t* bytes = (const std::uint8_t*)&*itr++;
					std::copy(bytes, bytes + element_size, &buffer[size]);
					size += element_size;
				}

				if (UpdateFx(_context, buffer, size) != 1)
					BOOST_THROW_EXCEPTION(evp_error());
			}

			return itr;
		}

		template <class Output>
		Output finalize(Output first) {
			std::uint8_t buffer[2*EVP_MAX_BLOCK_LENGTH];

			unsigned int written;
			if (FinalFx(_context, buffer, &written) != 1)
				written = 0;

			return std::copy(buffer, buffer + written, first);
		}

	};

}

namespace cryptox {

	template <class Algorithm>
	struct basic_message_digester : public evp_message_digest_context<
		Algorithm,
		EVP_DigestInit_ex,
		EVP_DigestUpdate,
		EVP_DigestFinal_ex
	> {
		template <class Input, class Output>
		Output operator()(Input first, Input last, Output d_first) {
			this->reset();
			this->update(first, last);
			return this->finalize(d_first);
		}
	};

}
