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
#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_HDR_ARRAY
#  include <boost/array.hpp>
	namespace cryptox {
		template <typename T, std::size_t N>
		struct array {
			typedef boost::array<T, N> type;
		};
	}
#else
#  include <array>
	namespace cryptox {
		template <typename T, std::size_t N>
		struct array {
			typedef std::array<T, N> type;
		};
	}
#endif

namespace cryptox {

	template <std::size_t Bits>
	struct block {
		BOOST_STATIC_ASSERT(Bits%8 == 0);

		typedef typename array<
			std::uint8_t,
			Bits/8
		>::type type;
	};

}
