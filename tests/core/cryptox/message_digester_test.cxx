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
#include <cryptox/message_digester.hxx>
#include <cryptox/hex_string.hxx>

BOOST_AUTO_TEST_CASE(evp_registry_test) {
//	assert(Digest::digest_size == EVP_MD_size(Digest::evp_message_digest()()));
}

BOOST_AUTO_TEST_CASE(sha_message_digester_test) {
	cryptox::message_digester<cryptox::sha256> digester;
	digester.update("abc", 3);
}
