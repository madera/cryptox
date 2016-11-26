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
#include "../detail/has_member_trait.hxx"
#include "message_digester.hxx"
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>

#define CRYPTOX_READ_BUFFER_SIZE 8192

namespace cryptox {

	namespace detail {

		DEFINE_HAS_MEMBER_TRAIT(begin)
		DEFINE_HAS_MEMBER_TRAIT(end)
		DEFINE_HAS_NESTED_TYPE(const_iterator)

		template <class T>
		struct is_container : public boost::mpl::and_<
			has_member_begin<T>,
			has_member_end<T>,
			has_nested_type_const_iterator<T>
		> {};

	}

	template <class Algorithm, typename T>
	typename boost::enable_if_c<
		sizeof(T) == 1,
		typename Algorithm::digest_type
	>::type
	digest(const T* data, const size_t size) {
		message_digester<Algorithm> digester;
		digester.update((const std::uint8_t*)data, size);
		return digester.digest();
	}

	template <class Algorithm, typename InputIterator>
	typename boost::enable_if_c<
		sizeof(typename InputIterator::value_type) == 1,
		typename Algorithm::digest_type
	>::type
	digest(InputIterator begin, InputIterator end) {
		message_digester<Algorithm> digester;
		std::uint8_t buffer[CRYPTOX_READ_BUFFER_SIZE];

		while (begin != end) {
			int i = 0;
			for ( ; begin != end && i<sizeof(buffer); ++i)
				buffer[i] = *begin++;

			digester.update(buffer, i);
		}

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
