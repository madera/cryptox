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

	struct block_view {
		const void*  data;
		const size_t size;

		block_view()
		 : data(0), size(0) {
		}

		block_view(const void* data_, const size_t size_)
		 : data(data_), size(size_) {
		}
	};

	inline block_view to_block_view(const block_view& other) {
		return other;
	}

	template <class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		block_view
	>::type
	inline to_block_view(const POD* data, const size_t size) {
		return block_view(data, size);
	}

	template <class POD, size_t N>
	typename boost::enable_if<
		boost::is_pod<POD>,
		block_view
	>::type
	inline to_block_view(const POD (&data)[N]) {
		return block_view(data, N);
	}

	template <class POD, size_t N>
	typename boost::enable_if<
		boost::is_pod<POD>,
		block_view
	>::type
	inline to_block_view(const boost::array<POD, N>& array) {
		return block_view(array.data(), array.size()*sizeof(POD));
	}

	template <class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		block_view
	>::type
	inline to_block_view(const std::vector<POD>& pod_vector) {
		return block_view(pod_vector.data(), pod_vector.size()*sizeof(POD));
	}

	inline block_view to_block_view(const char* c_str) {
		return block_view(c_str, strlen(c_str));
	}

	inline block_view to_block_view(const std::string& string) {
		return block_view(string.c_str(), string.size());
	}

}
