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
#include <cryptox/message_digests/all.hxx>
using namespace cryptox;

// No specific binary tests done here. Instead we safely delegate them to
// hash<>'s internal tests, which depend on digest<>, which depends on
// message_digester<>.

BOOST_AUTO_TEST_CASE(message_digest_registry_bits_test) {
	BOOST_CHECK_EQUAL(md5   ::bits(), 128);
	BOOST_CHECK_EQUAL(sha   ::bits(), 160);
	BOOST_CHECK_EQUAL(sha1  ::bits(), 160);
	BOOST_CHECK_EQUAL(sha224::bits(), 224);
	BOOST_CHECK_EQUAL(sha256::bits(), 256);
	BOOST_CHECK_EQUAL(sha384::bits(), 384);
	BOOST_CHECK_EQUAL(sha512::bits(), 512);
}

BOOST_AUTO_TEST_CASE(message_digest_registry_names_test) {
	BOOST_CHECK_EQUAL(std::string("MD5"    ), md5   ::name());
	BOOST_CHECK_EQUAL(std::string("SHA"    ), sha   ::name());
	BOOST_CHECK_EQUAL(std::string("SHA-1"  ), sha1  ::name());
	BOOST_CHECK_EQUAL(std::string("SHA-224"), sha224::name());
	BOOST_CHECK_EQUAL(std::string("SHA-256"), sha256::name());
	BOOST_CHECK_EQUAL(std::string("SHA-384"), sha384::name());
	BOOST_CHECK_EQUAL(std::string("SHA-512"), sha512::name());
}
