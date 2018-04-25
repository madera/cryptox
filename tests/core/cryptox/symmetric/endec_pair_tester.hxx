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
#include <cryptox/symmetric/symmetric_algorithm.hxx>
#include <cryptox/symmetric/encryptor.hxx>
#include <cryptox/symmetric/decryptor.hxx>
#include <cryptox/detail/make_random_vector.hxx>

namespace cryptox {

	namespace tests {

		template <class Algorithm>
		struct endec_pair_tester {
			typedef std::vector<std::uint8_t> buffer_type;

			const buffer_type key;
			const buffer_type salt;
			const buffer_type iv;

			cryptox::encryptor<Algorithm> encryptor;
			cryptox::decryptor<Algorithm> decryptor;

			endec_pair_tester()
			 : key(detail::make_random_vector()),
			  salt(detail::make_random_vector()),
			    iv(detail::make_random_vector()),
			  encryptor(key.begin(), key.end(), iv.begin(), iv.end()),
			  decryptor(key.begin(), key.end(), iv.begin(), iv.end()) {
			}

			template <class Container>
			void check_roundtrip(const Container& source) {
				buffer_type ciphertext;
				encryptor(source.begin(), source.end(), std::back_inserter(ciphertext));
				BOOST_CHECK_EQUAL(ciphertext.size(), Algorithm::ciphertext_size_for(source.size()));

				buffer_type plaintext;
				decryptor(ciphertext.begin(), ciphertext.end(), std::back_inserter(plaintext));
				BOOST_CHECK_EQUAL(plaintext.size(), source.size());

				BOOST_CHECK_EQUAL_COLLECTIONS(source.begin(), source.end(), plaintext.begin(), plaintext.end());
			}
		};

	}

}
