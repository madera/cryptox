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

//
// TODO: Will this stand the test of time?
//
// Currently we borrow the code from Boost Spirit. In the future, we may need to reimplement it.
//
#include <boost/spirit/home/support/container.hpp>

namespace cryptox { namespace detail {

	template <typename T>
	struct is_container : boost::spirit::traits::is_container<T> {};

}}
