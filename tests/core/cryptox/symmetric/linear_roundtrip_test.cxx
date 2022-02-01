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

#define TEST_NAME_SUFFIX _linear_roundtrip_test

template <class Algorithm>
static void test_linear_roundtrip(const size_t buffer_size = 4096) {
	cryptox::tests::endec_pair_tester<Algorithm> endec;

	typedef std::vector<std::uint8_t> buffer_type;

	using cryptox::detail::make_random_vector;
	const buffer_type master = make_random_vector(buffer_size);
	for (int i=0; i<=master.size(); ++i) {
		endec.check_roundtrip(
			buffer_type(master.begin(), master.begin() + i)
		);
	}
}

#define LINEAR_ROUNDTRIP_TEST(algorithm, description)                     \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm, TEST_NAME_SUFFIX)) { \
		test_linear_roundtrip<cryptox::algorithm>();              \
	}

CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(LINEAR_ROUNDTRIP_TEST)
