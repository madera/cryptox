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
#include "detail/symmetric_algorithm_pp.hxx"
#include "../detail/openssl.hxx"
#include "manifest.hxx"

namespace cryptox {

	template <openssl::cipher_fx_t Cipher>
	struct symmetric_algorithm {
		static const EVP_CIPHER* cipher() {
			return Cipher();
		}

		static int nid() {
			return EVP_CIPHER_nid(Cipher());
		}

		static const char* name() {
			return EVP_CIPHER_name(Cipher());
		}

		static size_t block_size() {
			return EVP_CIPHER_block_size(Cipher());
		}

		static size_t key_size() {
			return EVP_CIPHER_key_length(Cipher());
		}

		static size_t iv_size() {
			return EVP_CIPHER_iv_length(Cipher());
		}

		static std::uint64_t flags() {
			return EVP_CIPHER_flags(Cipher());
		}

		static bool mode() {
			return flags() & EVP_CIPH_MODE;
		}

		static size_t ciphertext_size_for(const size_t plaintext) {
			const size_t pz = plaintext;
			const size_t bz = block_size();
			return (bz == 1)? pz : (pz/bz + 1)*bz;
		}
	};

}

#define CRYPTOX_SYMMETRIC_ALGORITHM(algorithm, description) \
	namespace cryptox {                                 \
		typedef symmetric_algorithm<                \
			BOOST_PP_CAT(EVP_,algorithm)        \
		> algorithm;                                \
	}

//
// Define all known algorithms.
//
CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(CRYPTOX_SYMMETRIC_ALGORITHM)
