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
#include <fstream>

namespace cryptox {

	namespace detail {

		static inline size_t ifstream_size(std::ifstream& ifstream) {
			const size_t tmp = ifstream.tellg();
			ifstream.seekg(0, std::ios::end);
			const size_t result = ifstream.tellg();
			ifstream.seekg(tmp);
			return result;
		}

	}

}
