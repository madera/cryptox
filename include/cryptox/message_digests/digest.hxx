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
#include <boost/mpl/and.hpp>
#include "message_digester.hxx"
#include <boost/utility/enable_if.hpp>

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
		// TODO: Read data sequentially.
		return typename Algorithm::digest_type();
	}

	template <class Algorithm, typename Container>
	typename boost::enable_if<
		detail::is_container<Container>,
		typename Algorithm::digest_type
	>::type
	digest(const Container& container) {
		message_digester<Algorithm> digester;
		digester.update((const std::uint8_t*)&container[0], container.size());
		return digester.digest();
	}

}
