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
#include <cryptox/symmetric/decryptor.hxx>
#include <cryptox/detail/make_random_vector.hxx>

typedef std::vector<std::uint8_t> buffer_type;

template <class Algorithm>
struct endec_pair {
	typedef std::vector<std::uint8_t> buffer_type;

	const buffer_type key;
	const buffer_type salt;
	const buffer_type iv;

	cryptox::encryptor<Algorithm> encryptor;
	cryptox::decryptor<Algorithm> decryptor;

	endec_pair()
	 :  key(cryptox::detail::make_random_vector()),
	   salt(cryptox::detail::make_random_vector()),
	     iv(cryptox::detail::make_random_vector()),
	  encryptor(key.begin(), key.end(), iv.begin(), iv.end()),
	  decryptor(key.begin(), key.end(), iv.begin(), iv.end())
	{
	}
};

template <class Algorithm>
void linear_roundtrip_endec_test(const size_t buffer_size = 16384) {
	::endec_pair<Algorithm> endec;

	const buffer_type master_source = cryptox::detail::make_random_vector(buffer_size);

	for (int i=0; i<=master_source.size(); ++i) {
		const buffer_type source(master_source.begin(), master_source.begin() + i);

		buffer_type ciphertext;
		endec.encryptor(source.begin(), source.end(), std::back_inserter(ciphertext));
//		BOOST_CHECK_EQUAL(ciphertext.size(), endec.encryptor.ciphertext_size_for(source.size()));

		buffer_type plaintext;
		endec.decryptor(ciphertext.begin(), ciphertext.end(), std::back_inserter(plaintext));
		BOOST_CHECK_EQUAL(plaintext.size(), source.size());

		BOOST_CHECK_EQUAL_COLLECTIONS(source.begin(), source.end(), plaintext.begin(), plaintext.end());

		if (true && i%1024 == 0)
			std::cerr << "static_roundtrip_endec_test"
			          << " sz=" << source.size()
			          << " ctz=" << ciphertext.size()
			          << " ptz=" << plaintext.size()
			          << std::endl;
	}
}

template <class Algorithm>
void quadratic_roundtrip_endec_test(const size_t rounds = 8192) {
	::endec_pair<Algorithm> endec;

	for (int i=0; i<=rounds; ++i) {
		const buffer_type source = cryptox::detail::make_random_vector(i);

		buffer_type ciphertext;
		endec.encryptor(source.begin(), source.end(), std::back_inserter(ciphertext));
//		BOOST_CHECK_EQUAL(ciphertext.size(), endec.encryptor.ciphertext_size_for(source.size()));

		buffer_type plaintext;
		endec.decryptor(ciphertext.begin(), ciphertext.end(), std::back_inserter(plaintext));
		BOOST_CHECK_EQUAL(plaintext.size(), source.size());

		BOOST_CHECK_EQUAL_COLLECTIONS(source.begin(), source.end(), plaintext.begin(), plaintext.end());

		if (true && i%1024 == 0)
			std::cerr << "quadratic_roundtrip_endec_test"
			          << " sz=" << source.size()
			          << " ctz=" << ciphertext.size()
			          << " ptz=" << plaintext.size()
			          << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(multiple_roundtrip_endec_test) {
	using namespace cryptox;

	   linear_roundtrip_endec_test<aes_128_cbc>();
	quadratic_roundtrip_endec_test<aes_128_cbc>();

	   linear_roundtrip_endec_test<aes_192_cbc>();
	quadratic_roundtrip_endec_test<aes_192_cbc>();

	   linear_roundtrip_endec_test<aes_256_cbc>();
	quadratic_roundtrip_endec_test<aes_256_cbc>();
}
