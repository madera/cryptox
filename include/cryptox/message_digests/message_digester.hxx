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
#include "../detail/is_container.hxx"
#include "../exceptions.hxx"
#include "detail/message_digest_traits.hxx"
#include <boost/exception/exception.hpp>
#include <boost/optional.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#ifndef CRYPTOX_NO_IFSTREAM
#include <fstream>
#endif

namespace cryptox {

	template <class Algorithm>
	struct message_digester : boost::noncopyable {
		typedef message_digester this_type;
		typedef typename Algorithm::digest_type digest_type;

		static const size_t read_buffer_size = 64*1024;

		message_digester() {
			_context = EVP_MD_CTX_create();
			if (!_context)
				throw std::bad_alloc();

			if (EVP_DigestInit_ex(_context, Algorithm::evp_md(), NULL) == 0)
				BOOST_THROW_EXCEPTION(evp_error());
		}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
		message_digester(this_type&& other) {
			_context = other._context;
			other._context = nullptr;
		}
#endif

		~message_digester() {
			if (_context)
				EVP_MD_CTX_destroy(_context);
		}

		this_type& update(const char* c_string) {
			if (EVP_DigestUpdate(_context, (const std::uint8_t*)c_string, strlen(c_string)) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
			return *this;
		}

		template <typename T>
		typename boost::enable_if_c<
			sizeof(T) == 1,
			this_type&
		>::type
		update(const T* data, const size_t size) {
			if (EVP_DigestUpdate(_context, (const std::uint8_t*)data, size) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
			return *this;
		}

		template <typename InputIterator>
		typename boost::enable_if_c<
			sizeof(typename InputIterator::value_type) == 1,
			this_type&
		>::type
		update(InputIterator begin, InputIterator end) {
			std::uint8_t buffer[read_buffer_size];
			while (begin != end) {
				int i = 0;
				for ( ; begin != end && i<sizeof(buffer); ++i)
					buffer[i] = *begin++;

				update(buffer, i);
			}

			return *this;
		}

		template <typename Container>
		typename boost::enable_if<
			detail::is_container<Container>
		>::type
		update(const Container& container) {
			return (*this)(
				boost::begin(container),
				boost::end(container)
			);
		}

		this_type& update(std::ifstream& file, boost::optional<size_t> max = boost::none) {
			std::ifstream::char_type buffer[read_buffer_size];

			size_t total_read = 0;
			size_t current_read = 0;

			do {
				file.read(buffer, sizeof(buffer));
				current_read = file.gcount();
				if (current_read > 0) {
					update(buffer, current_read);
					total_read += current_read;
				}
			} while (current_read > 0 && file);

			return *this;
		}

		digest_type digest() {
			digest_type result;
			if (EVP_DigestFinal_ex(_context, result.data(), 0) == 0)
				BOOST_THROW_EXCEPTION(evp_error());
			return result;
		}

	private:
		EVP_MD_CTX* _context;
	};

}
