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
#include "../block.hxx"
#include "../detail/openssl.hxx"

namespace cryptox {
	template <std::size_t Bits>
	struct message_digester_algorithm {
		BOOST_STATIC_ASSERT(Bits%8 == 0);

		typedef block<Bits> digest_type;

		static const int bits() {
			return Bits;
		}
	};
}

#define CRYPTOX_MESSAGE_DIGEST(algorithm, algorithm_bits, algorithm_name)   \
	struct algorithm : message_digester_algorithm<algorithm_bits> {     \
		static const EVP_MD* evp_md() { return EVP_##algorithm(); } \
		static const char*     name() { return algorithm_name;    } \
	};

namespace cryptox {
	CRYPTOX_MESSAGE_DIGEST(md5   , 128, "MD5"    );
	CRYPTOX_MESSAGE_DIGEST(sha   , 160, "SHA"    );
	CRYPTOX_MESSAGE_DIGEST(sha1  , 160, "SHA-1"  );
	CRYPTOX_MESSAGE_DIGEST(sha224, 224, "SHA-224");
	CRYPTOX_MESSAGE_DIGEST(sha256, 256, "SHA-256");
	CRYPTOX_MESSAGE_DIGEST(sha384, 384, "SHA-384");
	CRYPTOX_MESSAGE_DIGEST(sha512, 512, "SHA-512");
// TODO: EVP_mdc2
// TODO: EVP_ripemd160
}

#undef CRYPTOX_MESSAGE_DIGEST
