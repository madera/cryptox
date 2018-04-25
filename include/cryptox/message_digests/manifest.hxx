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

#pragma once

#define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_NULL \
	((md_null, 0, "UNDEF"))

#ifdef OPENSSL_NO_MDC2
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MDC2
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MDC2 \
	((mdc2, 128, "MDC2"))
#endif

#ifdef OPENSSL_NO_MD2
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD2
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD2 \
	((md2, 128, "MD2"))
#endif

#ifdef OPENSSL_NO_MD4
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD4
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD4 \
	((md4, 128, "MD4"))
#endif

#ifdef OPENSSL_NO_MD5
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD5
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD5 \
	((md5, 128, "MD5"))
#endif

#ifdef OPENSSL_NO_SHA
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA \
	((sha,   160, "SHA"            )) \
	((sha1,  160, "SHA1"           )) \
	((dss,   160, "DSA-SHA"        )) \
	((dss1,  160, "DSA"            )) \
	((ecdsa, 160, "ecdsa-with-SHA1"))
#endif

#ifdef OPENSSL_NO_SHA256
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA256
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA256 \
	((sha224, 224, "SHA224" )) \
	((sha256, 256, "SHA256"))
#endif

#ifdef OPENSSL_NO_SHA512
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA512
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA512 \
	((sha384, 384, "SHA384" )) \
	((sha512, 512, "SHA512"))
#endif

#ifdef OPENSSL_NO_RIPEMD
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_RIPEMD
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_RIPEMD \
	((ripemd160, 160, "RIPEMD160" ))
#endif

#ifdef OPENSSL_NO_WHIRLPOOL
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_WHIRLPOOL
#else
#  define CRYPTOX_MESSAGE_DIGEST_ALGORITHM_WHIRLPOOL \
	((whirlpool, 512, "whirlpool" ))
#endif

#define CRYPTOX_MESSAGE_DIGEST_ALGORITHMS          \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_NULL      \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MDC2      \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD2       \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD4       \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_MD5       \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA       \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA256    \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_SHA512    \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_RIPEMD    \
	CRYPTOX_MESSAGE_DIGEST_ALGORITHM_WHIRLPOOL
