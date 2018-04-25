// [===========================================================================]
// [                               C r y p t o x                               ]
// [---------------------------------------------------------------------------]
// [                                                                           ]
// [                          Copyright (C) 2016-2018                          ]
// [                      Rodrigo Madera <madera@acm.org>                      ]
// [                                                                           ]
// [---------------------------------------------------------------------------]
// [         Distributed under the Boost Software License, Version 1.0         ]
// [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
// [===========================================================================]

#pragma once
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

#define __CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(r, callback, elem) \
	callback(BOOST_PP_TUPLE_ELEM(2, 0, elem),                    \
	         BOOST_PP_TUPLE_ELEM(2, 1, elem))

#define CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(callback)                \
	BOOST_PP_SEQ_FOR_EACH(__CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM, \
	                      callback,                                  \
	                      CRYPTOX_SYMMETRIC_ALGORITHMS)
