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

typedef const EVP_MD* (*message_digest_fx_t)();

namespace cryptox {

	namespace detail {

		template <message_digest_fx_t Digest>
		struct message_digest_traits;

	}

}

// TODO: Move this somewhere else.
namespace cryptox { namespace detail {
	template <>
	struct message_digest_traits<EVP_sha256> {
		enum { digest_size = 256/8 };
		typedef boost::array<std::uint8_t, digest_size> digest_type;
	};
}}
