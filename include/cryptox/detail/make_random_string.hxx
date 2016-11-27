// [===========================================================================]
// [                               S p l o t c h                               ]
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
#include <string>
#include <random>

namespace cryptox {

	namespace detail {

		static inline std::string make_random_string(const size_t size = 32) {
			const char alphabet[] = "abcdefghijklmnopqrstuvwxyz0123456789";
			const size_t alphabet_size = sizeof(alphabet) - 1;

			std::string result(chars, ' ');
			for (char& c : result)
				c = alphabet[rand()%alphabet_size];

			return result;
		}

	}

}
