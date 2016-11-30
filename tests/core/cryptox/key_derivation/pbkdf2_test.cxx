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

#include "pch.hxx"
#include <cryptox/key_derivation/pbkdf2.hxx>
#include <cryptox/detail/hex_string.hxx>
using namespace cryptox;

//
// Test using RFC 6070 Test Vectors
// (https://www.ietf.org/rfc/rfc6070.txt)
//
BOOST_AUTO_TEST_CASE(pbkdf2_rfc6070_test) {
	{
		const bits<160>::type expected = {{
			0x0c, 0x60, 0xc8, 0x0f, 0x96, 0x1f, 0x0e, 0x71,
			0xf3, 0xa9, 0xb5, 0x24, 0xaf, 0x60, 0x12, 0x06,
			0x2f, 0xe0, 0x37, 0xa6
		}};

		BOOST_CHECK((pbkdf2<sha1, 160>("password", "salt", 1)) == expected);
	}
	{
		const bits<160>::type expected = {{
			0xea, 0x6c, 0x01, 0x4d, 0xc7, 0x2d, 0x6f, 0x8c,
			0xcd, 0x1e, 0xd9, 0x2a, 0xce, 0x1d, 0x41, 0xf0,
			0xd8, 0xde, 0x89, 0x57
		}};

		BOOST_CHECK((pbkdf2<sha1, 160>("password", "salt", 2)) == expected);
	}
	{
		const bits<160>::type expected = {{
			0x4b, 0x00, 0x79, 0x01, 0xb7, 0x65, 0x48, 0x9a,
			0xbe, 0xad, 0x49, 0xd9, 0x26, 0xf7, 0x21, 0xd0,
			0x65, 0xa4, 0x29, 0xc1
		}};

		BOOST_CHECK((pbkdf2<sha1, 160>("password", "salt", 4096)) == expected);
	}
	{
		const bits<160>::type expected = {{
			0xee, 0xfe, 0x3d, 0x61, 0xcd, 0x4d, 0xa4, 0xe4,
			0xe9, 0x94, 0x5b, 0x3d, 0x6b, 0xa2, 0x15, 0x8c,
			0x26, 0x34, 0xe9, 0x84
		}};

		BOOST_CHECK((pbkdf2<sha1, 160>("password", "salt", 16777216)) == expected);
	}
	{
		const bits<200>::type expected = {{
			0x3d, 0x2e, 0xec, 0x4f, 0xe4, 0x1c, 0x84, 0x9b,
			0x80, 0xc8, 0xd8, 0x36, 0x62, 0xc0, 0xe4, 0x4a,
			0x8b, 0x29, 0x1a, 0x96, 0x4c, 0xf2, 0xf0, 0x70,
			0x38
		}};

		BOOST_CHECK((pbkdf2<sha1, 200>(
			"passwordPASSWORDpassword",
			"saltSALTsaltSALTsaltSALTsaltSALTsalt",
			4096
		)) == expected);
	}
	{
		const bits<128>::type expected = {{
			0x56, 0xfa, 0x6a, 0xa7, 0x55, 0x48, 0x09, 0x9d,
			0xcc, 0x37, 0xd7, 0xf0, 0x34, 0x25, 0xe0, 0xc3
		}};

		BOOST_CHECK((pbkdf2<sha1, 128>("pass\0word", 9, "sa\0lt", 5, 4096)) == expected);
	}
}
