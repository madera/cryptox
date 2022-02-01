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

#define TEST_NAME_SUFFIX _padded_roundtrip_basic_endec_test

template <class Algorithm>
static void test_padded_roundtrip(const size_t buffer_size = 128) {
	typedef std::vector<std::uint8_t> buffer_type;
	const buffer_type master = cryptox::detail::make_random_vector(buffer_size);

	// NOTE: For now just test with 0 and block_size().
	for (int pad_size=0; pad_size<=Algorithm::block_size(); pad_size += Algorithm::block_size()) {
		cryptox::tests::endec_pair_tester<Algorithm> endec;
		endec.encryptor.padding(pad_size);
		endec.decryptor.padding(pad_size);

		for (int i=0; i<=master.size(); i += Algorithm::block_size()) {
			endec.check_roundtrip(
				buffer_type(master.begin(), master.begin() + i)
			);
		}
	}
}

#define PADDED_ROUNDTRIP_TEST(algorithm, description)                     \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm, TEST_NAME_SUFFIX)) { \
		test_padded_roundtrip<cryptox::algorithm>();              \
	}

// FIXME: This is broken.
//CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(PADDED_ROUNDTRIP_TEST)
