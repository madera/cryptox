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
#include <openssl/evp.h>

namespace cryptox {

	namespace openssl {

		//
		// Message Digests
		//

		typedef const EVP_MD* (*message_digest_fx_t)();

		typedef int (*message_digest_init_fx_t)(EVP_MD_CTX*,
		                                        const EVP_MD*,
		                                        ENGINE*);

		typedef int (*message_digest_update_fx_t)(EVP_MD_CTX*,
		                                          const void*,
		                                          size_t);

		typedef int (*message_digest_final_fx_t)(EVP_MD_CTX*,
		                                         std::uint8_t*,
		                                         unsigned int*);

		//
		// Ciphers
		//

		typedef const EVP_CIPHER* (*cipher_fx_t)();

		typedef int (*cipher_init_fx_t)(EVP_CIPHER_CTX*,
                                                const EVP_CIPHER*,
                                                ENGINE*,
                                                const std::uint8_t*,
                                                const std::uint8_t*);

		typedef int (*cipher_update_fx_t)(EVP_CIPHER_CTX*,
                                                  std::uint8_t*,
                                                  int*,
                                                  const std::uint8_t*,
                                                  int);

		typedef int (*cipher_final_fx_t)(EVP_CIPHER_CTX*,
                                                 std::uint8_t*,
                                                 int*);

	}

}
