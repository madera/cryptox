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
#include "../detail/exceptions.hxx"
#include "../message_digests/message_digest_algorithm.hxx"
#include "../block.hxx"
#include <boost/throw_exception.hpp>

namespace cryptox {

	template <
		class DigestAlgorithm,
		typename Key,
		typename Salt,
		typename Output
	>
	Output pbkdf2(Key   key_first, Key   key_last,
	              Salt salt_first, Salt salt_last,
	              const size_t rounds,
		      Output output,
		      const size_t bits = DigestAlgorithm::bits()) {

		std::vector<char> key;
		std::copy(key_first, key_last, std::back_inserter(key));

		std::vector<std::uint8_t> salt;
		std::copy(salt_first, salt_last, std::back_inserter(salt));

		std::uint8_t result[EVP_MAX_KEY_LENGTH];

		if (PKCS5_PBKDF2_HMAC(
			&key [0], key .size(),
			&salt[0], salt.size(),
			rounds,
			DigestAlgorithm::digest(),
			sizeof(result),
			result
		) != 1)
			BOOST_THROW_EXCEPTION(evp_error());

		Output itr = std::copy(result, result + bits/8, output);
		std::fill(result, result + sizeof(result), 0);

		return itr;
	}

}
