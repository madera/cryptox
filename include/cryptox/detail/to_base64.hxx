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
#include <cryptox/detail/openssl.hxx>
#include <string>
#include <iterator>

namespace cryptox {

	template <class Input, class Output>
	Output to_base64(Input first, Input last, Output d_first) {
		while (first != last) {
			std::uint8_t input[128];
			size_t input_size = 0;
			while (input_size < sizeof(input) && first != last)
				input[input_size++] = *first++;

			std::uint8_t output[160];
			const size_t output_size = EVP_EncodeBlock(output,
			                                           input,
			                                           input_size);

			d_first = std::copy(output, output + output_size, d_first);
		}

		return d_first;
	}

	template <class Input>
	std::string to_base64(Input first, Input last) {
		std::string result;
		to_base64(first, last, std::back_inserter(result));
		return result;
	}

	template <typename Container>
	std::string to_base64(const Container& container) {
		return to_base64(container.begin(), container.end());
	}

}
