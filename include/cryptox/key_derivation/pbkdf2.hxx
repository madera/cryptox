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
#include "../bits.hxx"
#include <boost/array.hpp>
#include <string>
#include <iterator>

namespace cryptox {

	template <class DigestAlgorithm, int Bits>
	typename bits<Bits>::type
	pbkdf2(
		const char* key, const size_t key_size,
		const std::uint8_t* salt, const size_t salt_size,
		const size_t rounds
	) {
		typename bits<Bits>::type result;

		if (PKCS5_PBKDF2_HMAC(
			key,  key_size,
			salt, salt_size,
			rounds,
			DigestAlgorithm::evp_md(),
			result.size(),
			result.data()
                ) != 1) {
			std::fill(result.begin(), result.end(), 0);
                }

                return result;
	}

	template <class DigestAlgorithm, int Bits>
	typename bits<Bits>::type
	pbkdf2(
		const char* key,  const size_t key_size,
		const char* salt, const size_t salt_size,
		const size_t rounds
	) {
		return pbkdf2<DigestAlgorithm, Bits>(
			key, key_size,
			(const std::uint8_t*)salt, salt_size,
			rounds
		);
	}

	template <class DigestAlgorithm, int Bits>
	typename bits<Bits>::type
	pbkdf2(const char* textual_key, const char* textual_salt, const size_t rounds) {
		return pbkdf2<DigestAlgorithm, Bits>(
			textual_key, strlen(textual_key),
			(const std::uint8_t*)textual_salt, strlen(textual_salt),
			rounds
		);
	}

	template <class DigestAlgorithm, int Bits>
	typename bits<Bits>::type
	pbkdf2(const std::string& key, const size_t rounds) {
		return pbkdf2<DigestAlgorithm, Bits>(
			key.c_str(), key.size(),
			0, 0,
			rounds
		);
	}

	template <class DigestAlgorithm, int Bits>
	typename bits<Bits>::type
	pbkdf2(const std::string& key, const std::string& salt, const size_t rounds) {
		return pbkdf2<DigestAlgorithm, Bits>(
			key.c_str(), key.size(),
			(const std::uint8_t*)salt.c_str(), salt.size(),
			rounds
		);
	}

}
