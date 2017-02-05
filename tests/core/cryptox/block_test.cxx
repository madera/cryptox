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
#include <boost/lexical_cast.hpp>
using namespace cryptox;

BOOST_AUTO_TEST_CASE(block_test) {
	{
		block<8> empty = {};
		const std::string hex = empty;
		BOOST_CHECK_EQUAL(hex, "00");
	}
	{
		block<16> empty = {};
		const std::string hex = empty;
		BOOST_CHECK_EQUAL(hex, "0000");
	}

	{
		block<32> block = { 0x12, 0x34, 0x56, 0x78 };
		BOOST_CHECK_EQUAL(static_cast<std::string>(block), "12345678");
	}
	{
		block<64> block = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
		BOOST_CHECK_EQUAL((std::string)block, "0123456789abcdef");
	}

	{
		block<64> block = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

		std::ostringstream oss;
		oss << block;

		BOOST_CHECK_EQUAL(oss.str(), "0123456789abcdef");
	}

	// Roadmap: Support boost::lexical_cast.
	// {
	//	block<72> block = { 0xb0, 0x05, 0x75, 0x1e, 0xc5, 0x1c, 0xa1, 0xca, 0x57 };
	//	BOOST_CHECK_EQUAL(boost::lexical_cast<std::string>(block), "b005751ec51ca1ca57");
	// }
}
