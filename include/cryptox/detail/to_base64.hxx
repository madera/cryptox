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
	namespace detail {
		template <class InputIterator, class OutputIterator>
		OutputIterator encode_base64_string(InputIterator first, InputIterator last, OutputIterator d_first) {
			// NOTE: Non-contiguous implementation.
			// TODO: Optimize for contiguous containers.
			// TODO: Add benchmark for non- vs contiguous encoding.

			while (first != last) {
				// Get three input bytes (24 bits) that will
				// become four base64 characters.
				// TODO: Match OpenSSL's internal size.
				std::uint8_t  input[3];
				std::uint8_t output[4];

				size_t input_size = 0;
				while (first != last && input_size < sizeof(input))
					input[input_size++] = *first++;

				EVP_EncodeBlock(output, input, input_size);

				for (size_t i=0; i<sizeof(output); ++i)
					*d_first++ = output[i];
			}

			return d_first;
		}
	}

	template <class InputIterator>
	std::string to_base64(InputIterator first, InputIterator last) {
		std::string result;
		detail::encode_base64_string(first, last, std::back_inserter(result));
		return result;
	}

	template <typename T>
	std::string to_base64(const T& x) {
		return to_base64(x.begin(), x.end());
	}

	template <class Generator>
	class to_base64_decorator {
		const Generator& _generator;
	public:
		to_base64_decorator(const Generator& generator)
		 : _generator(generator) {}

		template <typename T>
		std::string operator()(const T& x) const {
			return to_base64(_generator(x));
		}
	};
}
