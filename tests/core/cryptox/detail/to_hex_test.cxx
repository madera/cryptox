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
#include <cryptox/detail/to_hex.hxx>

BOOST_AUTO_TEST_CASE(empty_to_hex_test) {
	const std::string input    = "";
	const std::string expected = "";

	std::string output = cryptox::to_hex(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}

BOOST_AUTO_TEST_CASE(pangram_to_hex_test) {
	const std::string input    = "The quick brown fox jumps over the lazy dog";
	const std::string expected = "54686520717569636b2062726f776e20666f78206a7"
				     "56d7073206f76657220746865206c617a7920646f67";

	std::string output = cryptox::to_hex(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}
