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
#include "basic_endec.hxx"

namespace cryptox {

	template <cipher_fx_t Cipher>
	class encryptor : public basic_endec<Cipher, EVP_EncryptInit_ex, EVP_EncryptUpdate, EVP_EncryptFinal_ex> {
		typedef basic_endec<Cipher, EVP_EncryptInit_ex, EVP_EncryptUpdate, EVP_EncryptFinal_ex> base_type;
	public:
		encryptor(
			const char* key,  const size_t  key_size,
			const char* salt, const size_t salt_size,
			const char* iv,   const size_t   iv_size = encryptor<Cipher>::iv_size(),
			const size_t key_rounds = 64*1024
		) : base_type(key, key_size, salt, salt_size, iv, iv_size) {}

		encryptor(
			const char* textual_key, const char* textual_salt,
			const char* iv = 0, const size_t iv_size = encryptor<Cipher>::iv_size(),
			const size_t key_rounds = 64*1024
		) : base_type(
			textual_key,  strlen(textual_key),
			textual_salt, strlen(textual_salt),
			iv, iv_size,
			key_rounds
		) {}

		template <class InputIterator>
		encryptor(
			InputIterator  key_first, InputIterator  key_last,
			InputIterator salt_first, InputIterator salt_last,
			InputIterator   iv_first, InputIterator   iv_last,
			const int key_rounds = 64*1024
		) : base_type(
			 key_first,  key_last,
			salt_first, salt_last,
			  iv_first,   iv_last,
			key_rounds
		) {}
	};

}
