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

#include "pch.hxx"
#include <cryptox/symmetric/encryptor.hxx>
#include <cryptox/symmetric/symmetric_algorithm.hxx>

#define STATIC_CHECK(algorithm, description)       \
	BOOST_STATIC_ASSERT(                       \
		cryptox::detail::is_encryptor<     \
			cryptox::encryptor<        \
				cryptox::algorithm \
			>                          \
		>::value                           \
	);

static const void static_check_all() {
	CRYPTOX_PP_FOR_EACH_SYMMETRIC_ALGORITHM(STATIC_CHECK)
}
