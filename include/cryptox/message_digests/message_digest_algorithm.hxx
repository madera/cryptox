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
#include "../block.hxx"
#include "detail/message_digest_pp.hxx"
#include "../detail/openssl.hxx"
#include "manifest.hxx"

namespace cryptox {

	namespace detail {
		typedef const EVP_MD* (*digest_fx_t)();
	}

	template <detail::digest_fx_t Digest, std::size_t Bits>
	struct message_digest_algorithm {
		typedef typename block<
			Bits
		>::type digest_type;

		static int bits() {
			return Bits;
		}

		static const EVP_MD* digest() {
			return Digest();
		}

		static int type() {
			return EVP_MD_type(Digest());
		}

		static int nid() {
			return type();
		}

		static const char* name() {
			return EVP_MD_name(Digest());
		}

		static int pkey_type() {
			return EVP_MD_pkey_type(Digest());
		}

		static size_t size() {
			return EVP_MD_size(Digest());
		}

		static size_t block_size() {
			return EVP_MD_size(Digest());
		}

		static std::uint64_t flags() {
			return EVP_MD_flags(Digest());
		}
	};

}

#define CRYPTOX_MESSAGE_DIGEST_ALGORITHM(algorithm, bits, description) \
	namespace cryptox {                                            \
		typedef message_digest_algorithm<                      \
			BOOST_PP_CAT(EVP_,algorithm),                  \
			bits                                           \
		> algorithm;                                           \
	}

//
// Define all known algorithms.
//
CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(CRYPTOX_MESSAGE_DIGEST_ALGORITHM)
