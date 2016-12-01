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
#include "../message_digests/detail/message_digest_traits.hxx"
#include "../memory_block.hxx"
#include "../bits.hxx"

namespace cryptox {

	template <class DigestAlgorithm, int Bits, class Key, class Salt>
	typename bits<Bits>::type
	pbkdf2(Key key, Salt salt, const size_t rounds) {
		typename bits<Bits>::type result;

		const memory_block k = to_memory_block(key);
		const memory_block s = to_memory_block(salt);

		if (PKCS5_PBKDF2_HMAC(
			(const          char*)k.first, k.second,
			(const unsigned char*)s.first, s.second,
			rounds,
			DigestAlgorithm::evp_md(),
			result.size(),
			result.data()
                ) != 1) {
			std::fill(result.begin(), result.end(), 0);
                }

                return result;
	}

	template <class DigestAlgorithm, int Bits, class Key, class Salt>
	typename bits<Bits>::type
	pbkdf2(Key key, const size_t rounds) {
		typename bits<Bits>::type result;

		const memory_block k = to_memory_block(key);
		const memory_block s(0, 0);

		if (PKCS5_PBKDF2_HMAC(
			(const          char*)k.first, k.second,
			(const unsigned char*)s.first, s.second,
			rounds,
			DigestAlgorithm::evp_md(),
			result.size(),
			result.data()
                ) != 1) {
			std::fill(result.begin(), result.end(), 0);
                }

                return result;
	}

}
