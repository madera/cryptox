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
#include "../message_digests/all.hxx"
#include "../block_view.hxx"

namespace cryptox {

	template <class DigestAlgorithm, std::size_t Bits, class Key, class Salt>
	typename block<Bits>::type
	pbkdf2(Key key, Salt salt, const size_t rounds) {
		typename block<Bits>::type result;

		const block_view k = to_block_view(key);
		const block_view s = to_block_view(salt);

		if (PKCS5_PBKDF2_HMAC(
			(const          char*)k.data, k.size,
			(const unsigned char*)s.data, s.size,
			rounds,
			DigestAlgorithm::evp_md(),
			result.size(),
			result.data()
                ) != 1)
			BOOST_THROW_EXCEPTION(evp_error());

                return result;
	}

	template <class DigestAlgorithm, std::size_t Bits, class Key>
	typename block<Bits>::type
	pbkdf2(Key key, const size_t rounds) {
		return pbkdf2<DigestAlgorithm, Bits>(
			key,
			block_view(),
			rounds
                );
	}

}
