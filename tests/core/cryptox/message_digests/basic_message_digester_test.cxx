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

#define TEST_NAME_SUFFIX _message_digest_vectors_test

using std::string;
static const string empty_string;
static const string lazy_dog = "The quick brown fox jumps over the lazy dog";

#define ES(a, h) CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(a, empty_string, h)
#define LD(a, h) CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(a, lazy_dog    , h)

ES(md5, "d41d8cd98f00b204e9800998ecf8427e");
LD(md5, "9e107d9d372bb6826bd81d3542a419d6");

ES(sha1, "da39a3ee5e6b4b0d3255bfef95601890afd80709");
LD(sha1, "2fd4e1c67a2d28fced849ee1bb76e7391b93eb12");

ES(sha224, "d14a028c2a3a2bc9476102bb288234c415a2b01f828ea62ac5b3e42f");
LD(sha224, "730e109bd7a8a32b1cb9d9a09aa2325d2430587ddbc0c38bad911525");

ES(sha256, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
LD(sha256, "d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

ES(sha384, "38b060a751ac96384cd9327eb1b1e36a21fdb71114be0743"
           "4c0cc7bf63f6e1da274edebfe76f65fbd51ad2f14898b95b");
LD(sha384, "ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c49"
           "4011e3317dbf9a509cb1e5dc1e85a941bbee3d7f2afbc9b1");

ES(sha512, "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
           "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");
LD(sha512, "07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
           "2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6");

#define MESSAGE_DIGEST_VECTORS_TEST(algorithm, bits, description)         \
	BOOST_AUTO_TEST_CASE(BOOST_PP_CAT(algorithm, TEST_NAME_SUFFIX)) { \
		test::test_vector_registry<                               \
			cryptox::algorithm                                \
		>::test_all_vectors();                                    \
	}

CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(MESSAGE_DIGEST_VECTORS_TEST)

// TODO: Need more test data.
// TODO: Add truncated sha modes.
