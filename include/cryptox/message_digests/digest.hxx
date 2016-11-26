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
#include "message_digester.hxx"
#include <boost/mpl/or.hpp>

namespace cryptox {

	template <class Algorithm>
	typename Algorithm::digest_type
	digest(const char* c_string) {
		message_digester<Algorithm> digester;
		digester(c_string);
		return digester.digest();
	}

	template <class Algorithm, typename T>
	typename boost::enable_if_c<
		sizeof(T) == 1,
		typename Algorithm::digest_type
	>::type
	digest(const T* data, const size_t size) {
		message_digester<Algorithm> digester;
		digester(data, size);
		return digester.digest();
	}

	template <class Algorithm, typename InputIterator>
	typename boost::enable_if_c<
		sizeof(typename InputIterator::value_type) == 1,
		typename Algorithm::digest_type
	>::type
	digest(InputIterator begin, InputIterator end) {
		message_digester<Algorithm> digester;
		digester(begin, end);
		return digester.digest();
	}

	template <class Algorithm, typename Container>
	typename boost::enable_if<
		detail::is_container<Container>,
		typename Algorithm::digest_type
	>::type
	digest(const Container& container) {
		return digest<Algorithm>(
			boost::begin(container),
			boost::end(container)
		);
	}

}
