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
#include "../hex_string.hxx"
#include <string>

namespace cryptox {

	// TODO: Create a digest function for binary hashes.

	template <class Digest>
	std::string hash(const std::string& data) {
		message_digester<Digest> digester;
		digester.update(data.c_str(), data.size());
		return hex_string(digester.digest());
	}

}
