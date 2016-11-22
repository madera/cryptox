// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2017                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [                            All Rights Reserved                            ]
// [===========================================================================]

#pragma once
#include <string>
#include <iterator>

namespace cryptox {

	namespace detail {
		template <class InputIterator, class OutputIterator>
		OutputIterator copy_hex_string(InputIterator first, InputIterator last, OutputIterator d_first) {
			for (size_t i=0; first != last; ++i) {
				const bool high_nibble = (i%2 == 0);
				*d_first++ = "0123456789abcdef"[*first >> 4*high_nibble & 0x0f];
				if (!high_nibble)
					++first;
			}

			return d_first;
		}
	}

	template <class InputIterator>
	std::string hex_string(InputIterator first, InputIterator last) {
		std::string result;
		detail::copy_hex_string(first, last, std::back_inserter(result));
		return result;
	}

}
