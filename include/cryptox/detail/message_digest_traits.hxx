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

#pragma once
#include <openssl/evp.h>
#include <boost/array.hpp>

namespace cryptox {
	namespace detail {
		typedef const EVP_MD* (*evp_message_digest_fx_t)();

		template <evp_message_digest_fx_t Digest>
		struct message_digest_traits;
	}
}

#define CRYPTOX_EVP_MESSAGE_DIGEST(name, evp_fx, bits) \
	namespace cryptox { namespace detail { \
		template <> \
		struct message_digest_traits<evp_fx> { \
			enum { digest_size = bits/8 }; \
			typedef boost::array<std::uint8_t, digest_size> digest_type; \
			static evp_message_digest_fx_t evp_message_digest() { \
				return evp_fx; \
			} \
		}; \
	}} \
	namespace cryptox { \
		typedef detail::message_digest_traits<evp_fx> name; \
	}

// TODO: Move.
CRYPTOX_EVP_MESSAGE_DIGEST(md2,    EVP_md2,    128);
CRYPTOX_EVP_MESSAGE_DIGEST(md5,    EVP_md5,    128);
CRYPTOX_EVP_MESSAGE_DIGEST(sha,    EVP_sha,    160);
CRYPTOX_EVP_MESSAGE_DIGEST(sha1,   EVP_sha1,   160);
CRYPTOX_EVP_MESSAGE_DIGEST(sha224, EVP_sha224, 224);
CRYPTOX_EVP_MESSAGE_DIGEST(sha256, EVP_sha256, 256);
CRYPTOX_EVP_MESSAGE_DIGEST(sha384, EVP_sha384, 384);
CRYPTOX_EVP_MESSAGE_DIGEST(sha512, EVP_sha512, 512);
// TODO: EVP_mdc2
// TODO: EVP_ripemd160
