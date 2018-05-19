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
#include "basic_message_digester.hxx"
#include "message_digest_algorithm.hxx"

namespace cryptox {

	template <class Algorithm, class Container>
	typename Algorithm::digest_type
	digest(const Container& container) {
		typename Algorithm::digest_type result;
		basic_message_digester<Algorithm>()(container.begin(),
		                                    container.end(),
		                                    result.begin());
		return result;
	}

	template <class Algorithm, class POD>
	typename boost::enable_if<
		boost::is_pod<POD>,
		typename Algorithm::digest_type
	>::type
	digest(const POD* data, const size_t size) {
		typename Algorithm::digest_type result;
		basic_message_digester<Algorithm>()(data,
		                                    data + size,
		                                    result.begin());
		return result;
	}

	template <class Algorithm>
	typename Algorithm::digest_type
	digest(const char* c_str) {
		return digest<Algorithm>(c_str, strlen(c_str));
	}

}
