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
#include <cryptox/all.hxx>

BOOST_AUTO_TEST_CASE(all_test) {
	using namespace cryptox;

	{
		const std::string as_string = to_hex(digest<md5>("Hello world!"));
		BOOST_CHECK_EQUAL(as_string, "86fb269d190d2c85f6e0468ceca42a20");
	}

	{
		const char buffer[] = { 0x00, 0x10, 0x20, 0x30 };
		const std::string as_string = to_hex(digest<sha1>(buffer, sizeof(buffer)));
		BOOST_CHECK_EQUAL(as_string, "e89fc658068627378403ebfdcefcb13250579b50");
	}

	{
		std::vector<char> v;
		v.push_back(1); v.push_back(2); v.push_back(3); // C++03

		const std::string as_string = to_hex(digest<sha512>(v));
		const md5::digest_type as_bytes = digest<md5>("Hello world!");

		const md5::digest_type expected = {{
			0x86, 0xfb, 0x26, 0x9d, 0x19, 0x0d, 0x2c, 0x85,
			0xf6, 0xe0, 0x46, 0x8c, 0xec, 0xa4, 0x2a, 0x20
		}};

		BOOST_CHECK(as_bytes == expected);
	}
}
