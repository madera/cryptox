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
#include "message_digester.hxx"

namespace cryptox {

	template <class Algorithm, class MemoryBlock>
	typename Algorithm::digest_type
	digest(MemoryBlock block) {
		message_digester<Algorithm> digester;
		digester.update(block);
		return digester.digest();
	}

	template <class Algorithm, class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		typename Algorithm::digest_type
	>::type
	digest(const POD* data, const size_t size) {
		return digest<Algorithm>(block_view(data, size));
	}

	template <class Algorithm>
	typename Algorithm::digest_type
	digest(std::ifstream& file, boost::optional<size_t> max = boost::none) {
		message_digester<Algorithm> digester;
		digester.update(file);
		return digester.digest();
	}

	template <class Algorithm>
	struct digester {
		template <typename T>
		typename Algorithm::digest_type
		operator()(const T& x) const {
			return digest<Algorithm>(x);
		}
	};

}
