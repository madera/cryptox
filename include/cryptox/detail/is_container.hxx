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
#include "has_member_trait.hxx"
#include <boost/type_traits/is_pod.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>

namespace cryptox {

	namespace detail {

		DEFINE_HAS_MEMBER_TRAIT(begin)
		DEFINE_HAS_MEMBER_TRAIT(end)
		DEFINE_HAS_NESTED_TYPE(const_iterator)

		template <class T>
		struct is_container : boost::mpl::and_<
			boost::mpl::not_<boost::is_pod<T> >,
			has_member_begin<T>,
			has_member_end<T>,
			has_nested_type_const_iterator<T>
		> {};

	}

}
