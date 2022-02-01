// [===========================================================================]
// [                                M o n e t a                                ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2005-2015                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#include "pch.hxx"
#include <cryptox/detail/is_container.hxx>

#include <vector>
#include <string>
#include <list>

static void static_test() {
	using cryptox::detail::is_container;

	BOOST_MPL_ASSERT((is_container<std::string>));
	BOOST_MPL_ASSERT((is_container<std::vector<std::string> >));
	BOOST_MPL_ASSERT((is_container<std::list<std::string> >));

	BOOST_MPL_ASSERT_NOT((is_container<std::vector<std::string>*>));
	BOOST_MPL_ASSERT_NOT((is_container<int>));
	BOOST_MPL_ASSERT_NOT((is_container<float>));
	BOOST_MPL_ASSERT_NOT((is_container<void>));
}
