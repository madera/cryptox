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
#include "digest.hxx"
#include "../detail/hex_string.hxx"

namespace cryptox {

	template <class Algorithm, class MemoryBlock>
	std::string hash(MemoryBlock block) {
		return detail::hex_string(digest<Algorithm>(block));
	}

	template <class Algorithm, class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		std::string
	>::type
	hash(const POD* data, const size_t size) {
		return hash<Algorithm>(digest<Algorithm>(data, size));
	}

	template <class Algorithm>
	std::string hash(std::ifstream& file, boost::optional<size_t> max = boost::none) {
		return detail::hex_string(digest<Algorithm>(file, max));
	}

	// --------------------------------------------------------------------

	template <class Algorithm>
	struct hasher {
		template <typename T>
		std::string operator()(const T& x) const {
			return hash<Algorithm>(x);
		}
	};

}
