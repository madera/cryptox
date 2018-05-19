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
#include <openssl/rand.h>

namespace cryptox {

	template <class Output>
	void randomize(Output first, Output last) {
		while (first != last) {
			// Keep this low. It's expensive to get random bits.
			std::uint8_t input[16];
			RAND_bytes(input, sizeof(input));

			first = std::copy(input, input + sizeof(input), first);
		}
	}

}
