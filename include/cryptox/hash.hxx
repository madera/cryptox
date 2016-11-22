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
#include "message_digest.hxx"
#include "hex_string.hxx"
#include <string>

namespace cryptox {

	template <message_digest_fx_t Digest>
	std::string hash(const std::string& data) {
		message_digest<Digest> message_digest;
		message_digest.update(data.c_str(), data.size());
		return hex_string(message_digest.digest());
	}

}
