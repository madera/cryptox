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
#include <cryptox/detail/hex_string.hxx>

BOOST_AUTO_TEST_CASE(empty_detail_copy_hex_string_test) {
	const std::string input    = "";
	const std::string expected = "";

	std::string output;
	cryptox::detail::copy_hex_string(input.begin(), input.end(), std::back_inserter(output));
	BOOST_CHECK_EQUAL(output, expected);
}

BOOST_AUTO_TEST_CASE(pangram_detail_copy_hex_string_test) {
	const std::string input    = "The quick brown fox jumps over the lazy dog";
	const std::string expected = "54686520717569636b2062726f776e20666f78206a7"
				     "56d7073206f76657220746865206c617a7920646f67";

	std::string output;
	cryptox::detail::copy_hex_string(input.begin(), input.end(), std::back_inserter(output));
	BOOST_CHECK_EQUAL(output, expected);
}

BOOST_AUTO_TEST_CASE(empty_hex_string_test) {
	const std::string input    = "";
	const std::string expected = "";

	std::string output = cryptox::hex_string(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}

BOOST_AUTO_TEST_CASE(pangram_hex_string_test) {
	const std::string input    = "The quick brown fox jumps over the lazy dog";
	const std::string expected = "54686520717569636b2062726f776e20666f78206a7"
				     "56d7073206f76657220746865206c617a7920646f67";

	std::string output = cryptox::hex_string(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}
