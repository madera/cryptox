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
#include <boost/array.hpp>
#include <string>
#include <vector>
#include <utility>

namespace cryptox {

	struct memory_block {
		const void*  data;
		const size_t size;

		memory_block()
		 : data(0), size(0) {
		}

		memory_block(const void* data_, const size_t size_)
		 : data(data_), size(size_) {
		}
	};

	inline memory_block to_memory_block(const memory_block& other) {
		return other;
	}

	template <class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		memory_block
	>::type
	inline to_memory_block(const POD* data, const size_t size) {
		return memory_block(data, size);
	}

	template <class POD, size_t N>
	typename boost::enable_if<
		boost::is_pod<POD>,
		memory_block
	>::type
	inline to_memory_block(const POD (&data)[N]) {
		return memory_block(data, N);
	}

	template <class POD, size_t N>
	typename boost::enable_if<
		boost::is_pod<POD>,
		memory_block
	>::type
	inline to_memory_block(const boost::array<POD, N>& array) {
		return memory_block(array.data(), array.size()*sizeof(POD));
	}

	template <class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		memory_block
	>::type
	inline to_memory_block(const std::vector<POD>& pod_vector) {
		return memory_block(pod_vector.data(), pod_vector.size()*sizeof(POD));
	}

	inline memory_block to_memory_block(const char* c_str) {
		return memory_block(c_str, strlen(c_str));
	}

	inline memory_block to_memory_block(const std::string& string) {
		return memory_block(string.c_str(), string.size());
	}

}
