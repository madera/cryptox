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
#include <cryptox/message_digests/digest.hxx>
#include <cryptox/detail/make_random_string.hxx>
#include <cryptox/detail/ifstream_size.hxx>
using namespace cryptox;

static const std::string empty_string;
static const std::string lazy_dog = "The quick brown fox jumps over the lazy dog";

template <class Algorithm>
static void check_digests(const std::string& input, const char* expected) {
	BOOST_CHECK_EQUAL(to_hex(digest<Algorithm>(&input[0], input.size())), expected);
	BOOST_CHECK_EQUAL(to_hex(digest<Algorithm>(input.c_str())          ), expected);
	BOOST_CHECK_EQUAL(to_hex(digest<Algorithm>(input)                  ), expected);
}

BOOST_AUTO_TEST_CASE(md5_hash_test) {
	to_hex(empty_string);
	check_digests<md5>(empty_string, "d41d8cd98f00b204e9800998ecf8427e");
	check_digests<md5>(lazy_dog,     "9e107d9d372bb6826bd81d3542a419d6");
}

BOOST_AUTO_TEST_CASE(sha_hash_test) {
	check_digests<sha>(empty_string, "f96cea198ad1dd5617ac084a3d92c6107708c0ef");
	check_digests<sha>(lazy_dog,     "b03b401ba92d77666221e843feebf8c561cea5f7");
}

BOOST_AUTO_TEST_CASE(sha1_hash_test) {
	check_digests<sha1>(empty_string, "da39a3ee5e6b4b0d3255bfef95601890afd80709");
	check_digests<sha1>(lazy_dog,     "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12");
}

BOOST_AUTO_TEST_CASE(sha224_hash_test) {
	check_digests<sha224>(empty_string, "d14a028c2a3a2bc9476102bb2882"
					    "34c415a2b01f828ea62ac5b3e42f");
	check_digests<sha224>(lazy_dog,     "730e109bd7a8a32b1cb9d9a09aa2"
					    "325d2430587ddbc0c38bad911525");
}

BOOST_AUTO_TEST_CASE(sha256_hash_test) {
	check_digests<sha256>(empty_string, "e3b0c44298fc1c149afbf4c8996fb924"
					    "27ae41e4649b934ca495991b7852b855");
	check_digests<sha256>(lazy_dog,     "d7a8fbb307d7809469ca9abcb0082e4f"
					    "8d5651e46d3cdb762d02d0bf37c9e592");
}

BOOST_AUTO_TEST_CASE(sha384_hash_test) {
	check_digests<sha384>(empty_string, "38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
					    "4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b");
	check_digests<sha384>(lazy_dog,     "ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c49"
					    "4011e3317dbf9a509cb1e5dc1e85a941bbee3d7f2afbc9b1");
}

BOOST_AUTO_TEST_CASE(sha512_hash_test) {
	check_digests<sha512>(empty_string, "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
					    "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
	check_digests<sha512>(lazy_dog,     "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
					    "2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6");
}

BOOST_AUTO_TEST_CASE(simple_ifstream_test) {
	const std::string filename = std::tmpnam(0);

	/* Create temporary file */ {
		std::ofstream output_file(filename);
		if (!output_file)
			throw std::runtime_error("Failed to create file for tests.");

		output_file << lazy_dog;
		output_file.close();
	}

	/* Digest the file */ {
		std::ifstream input_file(filename);
		if (!input_file)
			throw std::runtime_error("Failed to open test file.");

		const char* expected = "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
				       "2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6";

		BOOST_CHECK_EQUAL(to_hex(digest<sha512>(input_file)), expected);
		input_file.close();

		std::remove(filename.c_str());
	}
}

BOOST_AUTO_TEST_CASE(digester_test) {
	std::vector<std::string> input;
	input.push_back(empty_string);
	input.push_back(lazy_dog);

	std::vector<std::string> expected;
	expected.push_back("d41d8cd98f00b204e9800998ecf8427e"); // MD5 for empty_string.
	expected.push_back("9e107d9d372bb6826bd81d3542a419d6"); // MD5 for lazy_dog.

	std::vector<std::string> digested;
	std::transform(
		input.begin(), input.end(),
		std::back_inserter(digested),
		to_hex_decorator<
			digester<md5>
		>(digester<md5>())
	);

	BOOST_CHECK_EQUAL_COLLECTIONS(digested.begin(), digested.end(), expected.begin(), expected.end());
}
