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

	template <class Algorithm>
	class encryptor : public basic_endec<
		Algorithm,
		EVP_EncryptInit_ex,
		EVP_EncryptUpdate,
		EVP_EncryptFinal_ex
	> {
		typedef basic_endec<
			Algorithm,
			EVP_EncryptInit_ex,
			EVP_EncryptUpdate,
			EVP_EncryptFinal_ex
		> base_type;
	public:
		template <class KeyInputIterator, class IVInputIterator>
		encryptor(KeyInputIterator key_first, KeyInputIterator key_last,
		           IVInputIterator  iv_first,  IVInputIterator  iv_last
		) : base_type(key_first, key_last, iv_first, iv_last) {
		}
	};

}
