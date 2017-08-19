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
#include <cryptox/block.hxx>

BOOST_AUTO_TEST_CASE(block_test) {
	using namespace cryptox;

	{
		block<8>::type block = {};
		BOOST_CHECK_EQUAL(to_hex(block), "00");
	}
	{
		block<16>::type block = {};
		BOOST_CHECK_EQUAL(to_hex(block), "0000");
	}

	{
		block<32>::type block = { 0x12, 0x34, 0x56, 0x78 };
		BOOST_CHECK_EQUAL(to_hex(block), "12345678");
	}
	{
		block<64>::type block = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		BOOST_CHECK_EQUAL(to_hex(block), "0123456789abcdef");
	}
	{
		block<64>::type block = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		std::ostringstream oss;
		oss << block;
		BOOST_CHECK_EQUAL(oss.str(), "0123456789abcdef");
	}
}
