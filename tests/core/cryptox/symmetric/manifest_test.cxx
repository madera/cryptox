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
#include <cryptox/symmetric/symmetric_algorithm.hxx>

template <class Algorithm>
static void check_manifest(const std::string description) {
	BOOST_CHECK_EQUAL(Algorithm::name(), description);
}

#define SYMMETRIC_MANIFEST_TEST(algorithm, description)                          \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm,_symmetric_manifest_test)) { \
		check_manifest<cryptox::algorithm>(description);                 \
	}

CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(SYMMETRIC_MANIFEST_TEST)
