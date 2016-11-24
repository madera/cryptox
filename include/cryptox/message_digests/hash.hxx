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
#include "digest.hxx"
#include "../hex_string.hxx"

namespace cryptox {

	template <class Algorithm>
	std::string hash(const std::string& data) {
		return hex_string(digest<Algorithm>(data.c_str(), data.size()));
	}

}
