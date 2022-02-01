// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2021                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#pragma once
#include <string>

#include <openssl/crypto.h>

namespace cryptox {

	template <class Input, class Output>
	Output from_hex(Input first, Output d_first) {
		// FIXME: This is not a good implementation.
		// FIXME: Implement POD-style buffers.

		long length = 0;
		std::uint8_t* result = OPENSSL_hexstr2buf(first, &length);
		if (result) {
			memcpy(d_first, result, length);
			OPENSSL_free(result);
		}

		return d_first;
	}

}