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
				block.buffer.begin(),
				block.buffer.end(),
				std::back_inserter(result)
			);

			return result;
		}
	}

	template <std::size_t Bits>
	struct block {
		BOOST_STATIC_ASSERT(Bits%8 == 0);

		typedef block this_type;
		typedef boost::array<std::uint8_t, Bits/8>  buffer_type;

		buffer_type buffer;

		bool operator==(const this_type& other) const {
			return buffer == other.buffer;
		}

		//
		// boost::array<> wrapper:
		//

		typedef typename buffer_type::value_type                         value_type;
		typedef typename buffer_type::iterator                             iterator;
		typedef typename buffer_type::const_iterator                 const_iterator;
		typedef typename buffer_type::reverse_iterator             reverse_iterator;
		typedef typename buffer_type::const_reverse_iterator const_reverse_iterator;
		typedef typename buffer_type::reference                           reference;
		typedef typename buffer_type::const_reference               const_reference;
		typedef typename buffer_type::size_type                           size_type;
		typedef typename buffer_type::difference_type               difference_type;

		      iterator  begin()       { return buffer. begin(); }
		const_iterator  begin() const { return buffer. begin(); }
		const_iterator cbegin() const { return buffer.cbegin(); }

		      iterator  end()       { return buffer. end(); }
		const_iterator  end() const { return buffer. end(); }
		const_iterator cend() const { return buffer.cend(); }

		      reverse_iterator  rbegin()       { return buffer. rbegin(); }
		const_reverse_iterator  rbegin() const { return buffer. rbegin(); }
		const_reverse_iterator crbegin() const { return buffer.crbegin(); }

		      reverse_iterator  rend()       { return buffer. rend(); }
		const_reverse_iterator  rend() const { return buffer. rend(); }
		const_reverse_iterator crend() const { return buffer.crend(); }

		      reference operator[](size_type i)       { return buffer[i]; }
		const_reference operator[](size_type i) const { return buffer[i]; }

		      reference at(size_type i)       { return buffer.at(i); }
		const_reference at(size_type i) const { return buffer.at(i); }

		      reference front()       { return buffer.front(); }
		const_reference front() const { return buffer.front(); }

		      reference back()       { return buffer.back(); }
		const_reference back() const { return buffer.back(); }

		static size_type     size() { return buffer_type::size(); }
		static bool         empty() { return buffer_type::size(); }
		static size_type max_size() { return buffer_type::max_size(); }
		enum { static_size = buffer_type::static_size };

		void swap(this_type& other) {
			buffer.swap(other.buffer);
		}

		const_iterator data() const { return buffer.data(); }
		      iterator data()       { return buffer.data(); }

		iterator c_array() { return buffer.c_array(); }

		void assign(const_reference value) { buffer.assign(value); }
		void fill  (const_reference value) { buffer.fill(value); }

		//
		// Conversion operators
		//

		operator buffer_type&() {
			return buffer;
		}

		operator const buffer_type&() const {
			return buffer;
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
