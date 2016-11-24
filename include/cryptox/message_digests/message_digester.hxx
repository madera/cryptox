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
#include "../exceptions.hxx"
#include "detail/message_digest_traits.hxx"
#include <boost/exception/exception.hpp>
#include <boost/noncopyable.hpp>
#include <array>

namespace cryptox {

	template <class Algorithm>
	struct message_digester : boost::noncopyable {
		typedef message_digester this_type;
		typedef typename Algorithm::digest_type digest_type;

		message_digester() {
			_context = EVP_MD_CTX_create();
			if (!_context)
				throw std::bad_alloc();

			if (EVP_DigestInit_ex(_context, Algorithm::evp_md(), NULL) == 0)
				BOOST_THROW_EXCEPTION(evp_error());
		}

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
		message_digester(message_digest&& other) {
			_context = other._context;
			other._context = nullptr;
		}
#endif

		~message_digester() {
			if (_context)
				EVP_MD_CTX_destroy(_context);
		}

		template <typename Byte>
		this_type& update(const Byte* data, const size_t size) {
			if (EVP_DigestUpdate(_context, (const std::uint8_t*)data, size) != 1)
				BOOST_THROW_EXCEPTION(evp_error());
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
