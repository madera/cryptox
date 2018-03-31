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

	namespace detail {

		template <class Iterator>
		void randomize(Iterator begin, Iterator end) {
			for (Iterator itr = begin; itr != end; ++itr) {
				// TODO: Optimize for contiguous ranges.

				// We need to set one element at a time.
				std::uint8_t tmp;
				RAND_bytes(&tmp, 1);
				*itr = tmp;
			}
		}

	}

}
