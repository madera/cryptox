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

namespace cryptox {

	template <class Algorithm, typename Byte>
	typename Algorithm::digest_type digest(const Byte* data, const size_t size) {
		message_digester<Algorithm> digester;
		digester.update(data, size);
		return digester.digest();
	}

}
