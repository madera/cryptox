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
#include "randomize.hxx"
#include <vector>

namespace cryptox {

	namespace detail {

		static inline std::vector<std::uint8_t> make_random_vector(const size_t size = 32) {
			std::vector<std::uint8_t> result(size);
			randomize(result.begin(), result.end());
			return result;
		}

	}

}
