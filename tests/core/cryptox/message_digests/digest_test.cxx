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
#include <cryptox/message_digests/digest.hxx>
#include <cryptox/detail/to_hex.hxx>
using namespace cryptox;

#ifndef BOOST_NO_CXX11_AUTO_DECLARATIONS
BOOST_AUTO_TEST_CASE(cxx11_digest_test) {
	const auto hash = digest<md5>("Hello world!");
	const auto str = to_hex(hash);
	BOOST_CHECK_EQUAL(str, "86fb269d190d2c85f6e0468ceca42a20");
}
#endif

BOOST_AUTO_TEST_CASE(cxx03_digest_test) {
	const md5::digest_type hash = digest<md5>("Hello world!");
	const std::string str = to_hex(hash);
	BOOST_CHECK_EQUAL(str, "86fb269d190d2c85f6e0468ceca42a20");
}

BOOST_AUTO_TEST_CASE(c_array_digest_test) {
	const char c_array[] = { 0x00, 0x10, 0x20, 0x30 };
	const sha1::digest_type hash = digest<sha1>(c_array);
	const std::string str = to_hex(hash);
	BOOST_CHECK_EQUAL(str, "e89fc658068627378403ebfdcefcb13250579b50");
}

BOOST_AUTO_TEST_CASE(array_digest_test) {
	const cryptox::array<char, 4>::type array = { 0x00, 0x10, 0x20, 0x30 };
	const sha1::digest_type hash = digest<sha1>(array);
	const std::string str = to_hex(hash);
	BOOST_CHECK_EQUAL(str, "e89fc658068627378403ebfdcefcb13250579b50");
}

BOOST_AUTO_TEST_CASE(vector_digest_test) {
	const std::vector<char> vector = { 1, 2, 3, 4 };
	const md5::digest_type hash = digest<md5>(vector);
	const std::string str = to_hex(hash);
	BOOST_CHECK_EQUAL(str, "08d6c05a21512a79a1dfeb9d2a8f262f");
}
