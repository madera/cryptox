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
#include <cryptox/key_derivation/pbkdf2.hxx>
#include <cryptox/detail/to_hex.hxx>
using namespace cryptox;

template <class Algorithm>
void test(
	const size_t       bits,
	const std::string& key,
	const std::string& salt,
	const size_t       rounds,
	const std::string& expected
) {
	std::vector<std::uint8_t> result;

	pbkdf2<Algorithm>(key .begin(), key .end(),
	                  salt.begin(), salt.end(),
	                  rounds,
	                  std::back_inserter(result),
	                  bits);

	BOOST_CHECK_EQUAL(to_hex(result), expected);
}

//
// Testing using RFC 6070 Test Vectors
// (https://www.ietf.org/rfc/rfc6070.txt)
//
BOOST_AUTO_TEST_CASE(rfc6070_pbkdf2_test) {
	test<sha1>(160,
	           "password",
	           "salt",
	           1,
	           "0c60c80f961f0e71f3a9b524af6012062fe037a6");

	test<sha1>(160,
	           "password",
	           "salt",
	           2,
	           "ea6c014dc72d6f8ccd1ed92ace1d41f0d8de8957");

	test<sha1>(160,
	           "password",
	           "salt",
	           4096,
	           "4b007901b765489abead49d926f721d065a429c1");

	test<sha1>(160,
	           "password",
	           "salt",
	           16777216,
	           "eefe3d61cd4da4e4e9945b3d6ba2158c2634e984");

	test<sha1>(200,
	           "passwordPASSWORDpassword",
	           "saltSALTsaltSALTsaltSALTsaltSALTsalt",
	           4096,
	           "3d2eec4fe41c849b80c8d83662c0e44a8b291a964cf2f07038");

	test<sha1>(128,
	           std::string("pass\0word", 9),
	           std::string("sa\0lt", 5),
	           4096,
	           "56fa6aa75548099dcc37d7f03425e0c3");
}

BOOST_AUTO_TEST_CASE(saltless_pbkdf2_test) {
	test<sha1>(160,
	           "password",
	           "",
	           1,
	           "8754c32c64b0f524fc50c00f788135de2d2dd767");

	test<sha1>(160,
	           "password",
	           "",
	           1000,
	           "9723591cd1cfecb0efd7b027ea93b100334b2986");
}
