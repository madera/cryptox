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
#include <string>

namespace cryptox {

	template <class Input, class Output>
	Output to_hex(Input first, Input last, Output d_first) {
		bool is_high_nibble = true;
		while (first != last) {
			const int index = *first >> (is_high_nibble? 4 : 0);
			*d_first++ = "0123456789abcdef"[index & 0x0f];

			is_high_nibble = !is_high_nibble;
			if (is_high_nibble)
				++first;
		}

		return d_first;
	}

	template <class Input>
	std::string to_hex(Input first, Input last) {
		std::string result;
		to_hex(first, last, std::back_inserter(result));
		return result;
	}

	template <typename Container>
	std::string to_hex(const Container& container) {
		return to_hex(container.begin(), container.end());
	}

}
