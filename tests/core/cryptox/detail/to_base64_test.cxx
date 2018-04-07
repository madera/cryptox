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
#include <cryptox/detail/to_base64.hxx>

BOOST_AUTO_TEST_CASE(empty_to_base64_test) {
	const std::string input    = "";
	const std::string expected = "";

	std::string output = cryptox::to_base64(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}

BOOST_AUTO_TEST_CASE(pangram_to_base64_test) {
	const std::string input    = "The quick brown fox jumps over the lazy dog";
	const std::string expected = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==";

	std::string output = cryptox::to_base64(input.begin(), input.end());
	BOOST_CHECK_EQUAL(output, expected);
}
