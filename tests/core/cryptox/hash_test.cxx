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
#include <cryptox/message_digest.hxx>
#include <cryptox/hash.hxx>

BOOST_AUTO_TEST_CASE(sha256_hash_test) {
	BOOST_CHECK_EQUAL(
		cryptox::hash<EVP_sha256>(""),
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
	);

	BOOST_CHECK_EQUAL(
		cryptox::hash<EVP_sha256>("The quick brown fox jumps over the lazy dog"),
		"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"
	);
}

BOOST_AUTO_TEST_CASE(sha512_hash_test) {
	BOOST_CHECK_EQUAL(
		cryptox::hash<EVP_sha512>(""),
		"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
		"47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e"
	);

	BOOST_CHECK_EQUAL(
		cryptox::hash<EVP_sha512>("The quick brown fox jumps over the lazy dog"),
		"07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
		"2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6"
	);
}
