#include "pch.hxx"

#include <cryptox/symmetric/iostreams/basic_endec_filter.hxx>
#include <cryptox/symmetric/iostreams/evp_encryptor.hxx>
#include <cryptox/symmetric/iostreams/evp_decryptor.hxx>
#include <cryptox/detail/make_random_vector.hxx>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>
#include <iostream>

typedef cryptox::aes_256_cbc cipher_type;
static std::vector<std::uint8_t> iv  = cryptox::detail::make_random_vector(32);
static std::vector<std::uint8_t> key = cryptox::detail::make_random_vector(32);

template <typename Input, typename Output>
static void encrypt_using_filter(Input first, Input last, Output d_first) {
	std::cerr << "+++ encrypting using filter (" << std::distance(first, last) << " input bytes)" << std::endl;
	std::cerr << "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee" << std::endl;

	boost::iostreams::filtering_ostream output;
	output.push(cryptox::create_filter(
		new cryptox::encryptor<cipher_type> (
			key.begin(), key.end(),
			iv.begin(),  iv.end()
		)
	));
	output.push(d_first);

	// FIX FIX FIX
	auto input = (const char*)&(*first);

	boost::iostreams::write(output, input, std::distance(first, last));
//	output.reset();
}

template <typename Input, typename Output>
static void decrypt_using_filter(Input first, Input last, Output d_first) {
	std::cerr << "+++ decrypting using filter (" << std::distance(first, last) << " input bytes)" << std::endl;
	std::cerr << "dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd" << std::endl;

	// boost::iostreams::filtering_istream input;
	// input.push(boost::iostreams::evp_decryptor<EVP_aes_256_cbc>(g_key, g_salt, g_iv));
	// input.push(boost::iostreams::array_source(encrypted.data(), encrypted.size()));

	// std::vector<char> decrypted;
	// boost::iostreams::copy(input, std::back_inserter(decrypted));
	// return decrypted;

//////
	boost::iostreams::filtering_istream input;
	input.push(cryptox::create_filter(
		new cryptox::decryptor<cipher_type> (
			key.begin(), key.end(),
			iv.begin(),  iv.end()
		)
	));

// 	input.push(boost::iostreams::array_source(encrypted.data(), encrypted.size()));

	auto inputd = (const char*)&(*first); // XXXXX
 	input.push(boost::iostreams::array_source(inputd, std::distance(first, last)));

	std::vector<char> decrypted;
	boost::iostreams::copy(input, std::back_inserter(decrypted));
// 	boost::iostreams::copy(input, d_first);
	input.reset();
//	input.flush();

	std::cerr << " -> decrypted bytes using filter: " << decrypted.size() << std::endl;
	std::copy(decrypted.begin(), decrypted.end(), d_first);
}

// // ---------------------------------------------------------------------------------------------------------------------

template <typename Input, typename Output>
static Output encrypt_using_direct(Input first, Input last, Output d_first) {
	cryptox::encryptor<cipher_type> encryptor(key.begin(), key.end(), iv.begin(), iv.end());
	return encryptor(first, last, d_first);
}

template <typename Input, typename Output>
static Output decrypt_using_direct(Input first, Input last, Output d_first) {
	cryptox::decryptor<cipher_type> decryptor(key.begin(), key.end(), iv.begin(), iv.end());	
	return decryptor(first, last, d_first);
}

// // ---------------------------------------------------------------------------------------------------------------------

template <typename Input, typename Output>
static Output perform_encryptions(Input first, Input last, Output d_first) {
	std::vector<std::uint8_t> filter;
	std::vector<std::uint8_t> direct;

	encrypt_using_filter(first, last, std::back_inserter(filter));
	encrypt_using_direct(first, last, std::back_inserter(direct));

std::cerr << 'e' << 'Z' << std::distance(first, last)
	  << ' ' << 'F' << filter.size()
	  << ' ' << 'D' << direct.size() << std::endl;

	BOOST_CHECK_EQUAL_COLLECTIONS(filter.begin(), filter.end(), direct.begin(), direct.end());

	return std::copy(filter.begin(), filter.end(), d_first);
}

template <typename Input, typename Output>
static Output perform_decryptions(Input first, Input last, Output d_first) {
	std::vector<std::uint8_t> filter;
	std::vector<std::uint8_t> direct;

	decrypt_using_filter(first, last, std::back_inserter(filter));
	decrypt_using_direct(first, last, std::back_inserter(direct));

std::cerr << 'd' << 'Z' << std::distance(first, last)
	  << ' ' << 'F' << filter.size()
	  << ' ' << 'D' << direct.size() << std::endl;

	BOOST_CHECK_EQUAL_COLLECTIONS(filter.begin(), filter.end(), direct.begin(), direct.end());

	return std::copy(filter.begin(), filter.end(), d_first);
}

// ---------------------------------------------------------------------------------------------------------------------

template <typename Input>
static void roundtrip_test(Input first, Input last) {

	std::cerr << "---------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cerr << "RT" << std::distance(first, last) << std::endl;

	std::vector<std::uint8_t> encrypted;
	std::vector<std::uint8_t> decrypted;

	perform_encryptions(first,             last,            std::back_inserter(encrypted));
	perform_decryptions(encrypted.begin(), encrypted.end(), std::back_inserter(decrypted));

	BOOST_CHECK_EQUAL_COLLECTIONS(first, last, decrypted.begin(), decrypted.end());
}

BOOST_AUTO_TEST_CASE(basic_endec_filter_test) {
	std::vector<std::uint8_t> input = cryptox::detail::make_random_vector(4200);

	//
	// Slice input and test along...
	//
	const size_t initial = 4100;
	size_t increment = 100;
	for (size_t i=initial; i<input.size(); i+=increment)
		roundtrip_test(input.begin(), input.begin() + i);
}
