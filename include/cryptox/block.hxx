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
#include "detail/hex_string.hxx"
#include <boost/array.hpp>

namespace cryptox {

	template <std::size_t Bits>
	struct block {
		BOOST_STATIC_ASSERT(Bits%8 == 0);
		typedef boost::array<std::uint8_t, Bits/8>  type;
	};

}

#ifndef CRYPTOX_NO_IO
template <class Char, class Traits, std::size_t Bits>
std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& output, const cryptox::block<Bits>& block) {
	return output << to_hex(block);
}
#endif
