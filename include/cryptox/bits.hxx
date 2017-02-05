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
#include <boost/array.hpp>
#include <boost/static_assert.hpp>

namespace cryptox {

	template <std::size_t Bits>
	struct bits {
		BOOST_STATIC_ASSERT_MSG(Bits%8 == 0, "Bits must be a multiple of 8");
		typedef boost::array<std::uint8_t, Bits/8> type;
	};

}
