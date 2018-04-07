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
#include "../detail/randomize.hxx"
#include "../detail/to_base64.hxx"
#include "../detail/to_hex.hxx"
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <memory>

namespace cryptox {

	typedef unsigned char byte;

	typedef const EVP_CIPHER* (*cipher_fx_t)();
	typedef int (*  init_fx_t)(EVP_CIPHER_CTX*, const EVP_CIPHER*, ENGINE*, const byte*, const byte*);
	typedef int (*update_fx_t)(EVP_CIPHER_CTX*, byte*, int*, const byte*, int);
	typedef int (* final_fx_t)(EVP_CIPHER_CTX*, byte*, int*);

}

namespace cryptox {

	template <init_fx_t>
	struct is_encryptor_category : boost::false_type {};

	template <>
	struct is_encryptor_category<EVP_EncryptInit_ex> : boost::true_type {};

}

namespace cryptox {

	template <cipher_fx_t Cipher, init_fx_t InitFx, update_fx_t UpdateFx, final_fx_t FinalFx>
	class basic_endec : boost::noncopyable {
		typedef std::vector<std::uint8_t> buffer_type;

		buffer_type _key;
		buffer_type _salt;
		buffer_type _iv;

		EVP_CIPHER_CTX _context;
	private:
		void randomize_iv() {
			detail::randomize(_iv.begin(), _iv.end());
		}

	public:
		static size_t iv_size() {
			return EVP_CIPHER_iv_length(Cipher());
		}

		static size_t block_size() {
			return EVP_CIPHER_block_size(Cipher());
		}

		static size_t ciphertext_size_for(const size_t plaintext_size) {
			const size_t pz = plaintext_size;
			const size_t bz = block_size();
			return (pz/bz + 1)*bz;
		}

	public:
		template <class InputIterator>
		basic_endec(
			InputIterator  key_first, InputIterator  key_last,
			InputIterator salt_first, InputIterator salt_last,
			InputIterator   iv_first, InputIterator   iv_last,
			const int key_rounds = 64*1024
		) :  _key( key_first,  key_last),
		    _salt(salt_first, salt_last),
		      _iv(  iv_first,   iv_last) {

			_iv.resize(iv_size());

			EVP_CIPHER_CTX_init(&_context);

			uint8_t garbled_key[32];
			PKCS5_PBKDF2_HMAC_SHA1(
				(const char*)&_key[0],  _key.size(),
				&_salt[0], _salt.size(),
				key_rounds,
				EVP_CIPHER_key_length(Cipher()),
				garbled_key
			);

			InitFx(&_context, Cipher(), 0, garbled_key, &_iv[0]);

			BOOST_REQUIRE( is_encryptor_category<EVP_EncryptInit_ex>::value);
			BOOST_REQUIRE(!is_encryptor_category<EVP_DecryptInit_ex>::value);

			if (false)
				std::cerr << "--- is_encryptor=" << is_encryptor_category<InitFx>::value
				          << " block_size=" << block_size()
				          << "\nKey:"
				          << " size=" << EVP_CIPHER_key_length(Cipher())
				          << " bits=" << to_base64(_key.begin(), _key.end()) << '\n'
				          << " IV:"
				          << " size=" << iv_size()
				          << " bits=" << to_base64(_iv.begin(), _iv.end()) << '\n'
				          << " DK:"
				          << " size=" << sizeof(garbled_key)
				          << " bits=" << to_base64(garbled_key, garbled_key + sizeof(garbled_key)) << '\n';

			// Clear sensitive memory.
			std::fill(std::begin(garbled_key), std::end(garbled_key), 0);
			reset();
		}

		~basic_endec() {
			EVP_CIPHER_CTX_cleanup(&_context);
		}

		void reset() {
			InitFx(&_context, 0, 0, 0, 0);
		}

		buffer_type iv() const {
			return _iv;
		}

		template <class InputIterator>
		void iv(const InputIterator first, const InputIterator last) const {
			_iv.clear();
			std::copy(first, last, std::back_inserter(_iv));
		}

		template <class InputIterator, class OutputIterator>
		OutputIterator operator()(InputIterator input_first, InputIterator input_last, OutputIterator output_first) {
			reset();
			OutputIterator itr = update(input_first, input_last, output_first);
			return finalize(itr);
		}

		template <class InputIterator, class OutputIterator>
		OutputIterator update(InputIterator input_first, InputIterator input_last, OutputIterator output_first) {
			InputIterator input_itr = input_first;
			OutputIterator output_itr = output_first;

			while (input_itr != input_last) {
				std::uint8_t input_buffer[1024]; // XXX
				size_t input_buffer_size = 0;

				while (input_buffer_size < sizeof(input_buffer) && input_itr != input_last)
					input_buffer[input_buffer_size++] = *input_itr++;

				std::uint8_t output_buffer[1024+64]; // XXX
				int output_buffer_size = 0;

				const int result = UpdateFx(
					&_context,

					output_buffer,
					&output_buffer_size,

					input_buffer,
					input_buffer_size
				);

				if (result != 1)
					return output_first;

				if (false)
					std::cerr << "\t-U" << is_encryptor_category<InitFx>::value << "-"
						  << " written: " << output_buffer_size
						  //<< " data: " << to_base64(output_buffer, output_buffer + output_buffer_size)
						  << std::endl;

				output_itr = std::copy(output_buffer, output_buffer + output_buffer_size, output_itr);
			}

			return output_itr;
		}

		template <class OutputIterator>
		OutputIterator finalize(OutputIterator output_first) {
			std::uint8_t buffer[128]; // XXX

			int written = 0;
			const int result = FinalFx(&_context, buffer, &written);

			if (result != 1)
				written = 0;

			if (false)
				std::cerr << "\t-F" << is_encryptor_category<InitFx>::value << "-"
				          << " written: " << written
				          //<< " data: " << to_base64(buffer, buffer + written)
				          << std::endl;

			return std::copy(buffer, buffer + written, output_first);
		}
	};

}
