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

#pragma once
#include <openssl/evp.h>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>

namespace cryptox { namespace detail {

	typedef const EVP_MD* (*evp_message_digest_fx_t)();

	template <evp_message_digest_fx_t Digest, int Bits>
	struct message_digest_traits {
		BOOST_STATIC_ASSERT(Bits%8 == 0);
		enum { digest_size = Bits/8 };

		typedef boost::array<std::uint8_t, digest_size> digest_type;

		static const EVP_MD* evp_md() {
			return Digest();
		}
	};
}}

// TODO: REVIEW: Should these stay here?
namespace cryptox {
	typedef detail::message_digest_traits<EVP_md2,    128> md2;
	typedef detail::message_digest_traits<EVP_md5,    128> md5;
	typedef detail::message_digest_traits<EVP_sha,    160> sha;
	typedef detail::message_digest_traits<EVP_sha1,   160> sha1;
	typedef detail::message_digest_traits<EVP_sha224, 224> sha224;
	typedef detail::message_digest_traits<EVP_sha256, 256> sha256;
	typedef detail::message_digest_traits<EVP_sha384, 384> sha384;
	typedef detail::message_digest_traits<EVP_sha512, 512> sha512;
// TODO: EVP_mdc2
// TODO: EVP_ripemd160
}
