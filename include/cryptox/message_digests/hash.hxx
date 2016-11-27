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
#include "digest.hxx"
#include "../hex_string.hxx"

namespace cryptox {

	template <class Algorithm>
	std::string hash(const char* c_string) {
		return hex_string(digest<Algorithm>(c_string, strlen(c_string)));
	}

	template <class Algorithm, typename T>
	std::string hash(const T* data, const size_t size) {
		return hex_string(digest<Algorithm>(data, size));
	}

	template <class Algorithm, typename InputIterator>
	std::string hash(InputIterator begin, InputIterator end) {
		return hex_string(digest<Algorithm>(begin, end));
	}

	template <class Algorithm, typename Container>
	std::string hash(const Container& container) {
		return hex_string(digest<Algorithm>(container));
	}

	template <class Algorithm>
	struct hasher {
		template <typename T>
		std::string operator()(const T& x) const {
			return hash<Algorithm>(x);
		}
	};

}
