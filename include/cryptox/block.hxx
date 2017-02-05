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
	struct block;

	namespace detail {
		template <std::size_t Bits>
		std::string hex_string(const block<Bits>& block) {
			std::string result;
			detail::copy_hex_string(
				block.bits.begin(),
				block.bits.end(),
				std::back_inserter(result)
			);

			return result;
		}
	}

	template <std::size_t Bits>
	struct block {
		typedef block this_type;
		typedef boost::array<std::uint8_t, Bits/8> buffer_type;

		buffer_type bits;

		typename buffer_type::size_type size() const {
			return bits.size();
		}

		typename buffer_type::iterator data() {
			return bits.data();
		} 

		typename buffer_type::const_iterator data() const {
			return bits.data();
		} 

		bool operator==(const this_type& other) const {
			return bits == other.bits;
		}

		operator buffer_type&() {
			return bits;
		}

		operator const buffer_type&() const {
			return bits;
		}

		operator std::string() const {
			return detail::hex_string(*this);
		}
	};
}

#ifndef CRYPTOX_NO_IO
template <class Char, class Traits, std::size_t Bits>
std::basic_ostream<Char, Traits>&
operator<<(std::basic_ostream<Char, Traits>& output, const cryptox::block<Bits>& block) {
	return (output << static_cast<std::string>(block));
}
#endif
