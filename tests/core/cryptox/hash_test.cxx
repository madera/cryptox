// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2017                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [                            All Rights Reserved                            ]
// [===========================================================================]

#include "pch.hxx"
#include <cryptox/hash.hxx>
using namespace cryptox;

BOOST_AUTO_TEST_CASE(md2_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<md2>(""),
		"8350e5a3e24c153df2275c9f80692773"
	);

	BOOST_CHECK_EQUAL(
		hash<md2>("The quick brown fox jumps over the lazy dog"),
		"03d85a0d629d2c442e987525319fc471"
	);
}

BOOST_AUTO_TEST_CASE(md5_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<md5>(""),
		"d41d8cd98f00b204e9800998ecf8427e"
	);

	BOOST_CHECK_EQUAL(
		hash<md5>("The quick brown fox jumps over the lazy dog"),
		"9e107d9d372bb6826bd81d3542a419d6"
	);
}

BOOST_AUTO_TEST_CASE(sha_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha>(""),
		"f96cea198ad1dd5617ac084a3d92c6107708c0ef"
	);

	BOOST_CHECK_EQUAL(
		hash<sha>("The quick brown fox jumps over the lazy dog"),
		"b03b401ba92d77666221e843feebf8c561cea5f7"
	);
}

BOOST_AUTO_TEST_CASE(sha1_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha1>(""),
		"da39a3ee5e6b4b0d3255bfef95601890afd80709"
	);

	BOOST_CHECK_EQUAL(
		hash<sha1>("The quick brown fox jumps over the lazy dog"),
		"2fd4e1c67a2d28fced849ee1bb76e7391b93eb12"
	);
}

BOOST_AUTO_TEST_CASE(sha224_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha224>(""),
		"d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f"
	);

	BOOST_CHECK_EQUAL(
		hash<sha224>("The quick brown fox jumps over the lazy dog"),
		"730e109bd7a8a32b1cb9d9a09aa2325d2430587ddbc0c38bad911525"
	);
}

BOOST_AUTO_TEST_CASE(sha256_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha256>(""),
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
	);

	BOOST_CHECK_EQUAL(
		hash<sha256>("The quick brown fox jumps over the lazy dog"),
		"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"
	);
}

BOOST_AUTO_TEST_CASE(sha384_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha384>(""),
		"38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
		"4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b"
	);

	BOOST_CHECK_EQUAL(
		hash<sha384>("The quick brown fox jumps over the lazy dog"),
		"ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c49"
		"4011e3317dbf9a509cb1e5dc1e85a941bbee3d7f2afbc9b1"
	);
}

BOOST_AUTO_TEST_CASE(sha512_hash_test) {
	BOOST_CHECK_EQUAL(
		hash<sha512>(""),
		"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
		"47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e"
	);

	BOOST_CHECK_EQUAL(
		hash<sha512>("The quick brown fox jumps over the lazy dog"),
		"07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
		"2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6"
	);
}
