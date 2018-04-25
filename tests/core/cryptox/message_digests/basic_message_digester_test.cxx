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
#include "test_vector_registry.hxx"
#include <cryptox/message_digests/message_digest_algorithm.hxx>
#include <cryptox/message_digests/basic_message_digester.hxx>
using namespace cryptox;

static const std::string empty_string;
static const std::string lazy_dog = "The quick brown fox jumps over the lazy dog";

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(md5, empty_string, "d41d8cd98f00b204e9800998ecf8427e");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(md5, lazy_dog,     "9e107d9d372bb6826bd81d3542a419d6");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha, empty_string, "f96cea198ad1dd5617ac084a3d92c6107708c0ef");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha, lazy_dog,     "b03b401ba92d77666221e843feebf8c561cea5f7");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha1, empty_string, "da39a3ee5e6b4b0d3255bfef95601890afd80709");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha1, lazy_dog,     "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha224, empty_string, "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha224, lazy_dog,     "730e109bd7a8a32b1cb9d9a09aa2325d2430587ddbc0c38bad911525");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha256, empty_string, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha256, lazy_dog,     "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha384, empty_string, "38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
                                                         "4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha384, lazy_dog,     "ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c49"
                                                         "4011e3317dbf9a509cb1e5dc1e85a941bbee3d7f2afbc9b1");

CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha512, empty_string, "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
                                                         "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(sha512, lazy_dog,     "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
                                                         "2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6");

#define MESSAGE_DIGEST_VECTORS_TEST(algorithm, bits, description)                    \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm,_message_digest_vectors_test)) { \
		test::test_vector_registry<cryptox::algorithm>::test_all_vectors(); \
	}

CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(MESSAGE_DIGEST_VECTORS_TEST)
