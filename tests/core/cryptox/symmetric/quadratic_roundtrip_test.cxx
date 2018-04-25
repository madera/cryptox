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
#include "endec_pair_tester.hxx"

template <class Algorithm>
void quadratic_roundtrip_endec_test(const size_t rounds = 4096) {
	cryptox::tests::endec_pair_tester<Algorithm> endec;

	for (int i=0; i<=rounds; ++i) {
		using cryptox::detail::make_random_vector;
		endec.check_roundtrip(make_random_vector(i));
	}
}

#define QUADRATIC_ROUNDTRIP_TEST(algorithm, description)                          \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm,_quadratic_roundtrip_test)) { \
		quadratic_roundtrip_endec_test<cryptox::algorithm>();             \
	}

CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(QUADRATIC_ROUNDTRIP_TEST)
