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
#include <boost/exception/exception.hpp>
#include <boost/noncopyable.hpp>
#include <array>

namespace cryptox {

	struct evp_error : virtual std::exception, virtual boost::exception {};

}
