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

#include "pch.hxx"
#include <cryptox/message_digests/message_digest_algorithm.hxx>

#define TEST_NAME_SUFFIX _message_digest_manifest_test

template <class Algorithm>
static void check_manifest(const size_t bits, const std::string description) {
	BOOST_CHECK_EQUAL(Algorithm::size()*8, bits);
	BOOST_CHECK_EQUAL(Algorithm::bits(), bits);
	BOOST_CHECK_EQUAL(Algorithm::name(), description);
}

#define MESSAGE_DIGEST_MANIFEST_TEST(algorithm, bits, description)        \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm, TEST_NAME_SUFFIX)) { \
		check_manifest<cryptox::algorithm>(bits, description);    \
	}

CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(MESSAGE_DIGEST_MANIFEST_TEST)
