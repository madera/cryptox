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

#define __CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(r, callback, elem) \
	callback(BOOST_PP_TUPLE_ELEM(3, 0, elem),                         \
	         BOOST_PP_TUPLE_ELEM(3, 1, elem),                         \
	         BOOST_PP_TUPLE_ELEM(3, 2, elem))

#define CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(callback)                \
	BOOST_PP_SEQ_FOR_EACH(__CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM, \
	                      callback,                                       \
	                      CRYPTOX_MESSAGE_DIGEST_ALGORITHMS)
