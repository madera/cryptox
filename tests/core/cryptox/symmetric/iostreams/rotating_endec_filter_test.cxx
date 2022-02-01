#include "pch.hxx"

#include <cryptox/symmetric/iostreams/rotating_endec_filter.hxx>
#include <cryptox/symmetric/iostreams/evp_encryptor.hxx>
#include <cryptox/symmetric/iostreams/evp_decryptor.hxx>
#include <cryptox/symmetric/symmetric_algorithm.hxx>
#include <cryptox/symmetric/encryptor.hxx>
#include <cryptox/symmetric/decryptor.hxx>
#include <cryptox/detail/make_random_vector.hxx>

#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/copy.hpp>

#include <boost/foreach.hpp>
#include <boost/array.hpp>

#include <iostream>

static const std::size_t PERIOD = 512;

// ----------------------------------------------------------------------------

struct symmetric_secrets {
	std::vector<std::uint8_t> iv;
	std::vector<std::uint8_t> key;

	symmetric_secrets()
	 : iv(cryptox::detail::make_random_vector()),
	  key(cryptox::detail::make_random_vector()) {
	}
};

typedef cryptox::aes_256_cbc cipher_type;

static boost::array<symmetric_secrets, 2> secrets;

// ----------------------------------------------------------------------------

class rotation_key_provider {
	size_t _iterations;
public:
	rotation_key_provider()
	 : _iterations(0) {
	}

	symmetric_secrets operator()() {
		return secrets[_iterations++ % 2];
	}
};

// ----------------------------------------------------------------------------

template <typename Input, typename Output>
static void encrypt_using_filter(Input first, Input last, Output d_first) {
	const size_t input_size = std::distance(first, last);

	boost::iostreams::filtering_ostream output;
	output.push(
		cryptox::create_rotating_filter<
			cryptox::encryptor<cipher_type>
		>(rotation_key_provider(), PERIOD)
	);

	output.push(d_first);

	// Ugly, but effective for this test module.
	const char* input = (const char*)&(*first);

	boost::iostreams::write(output, input, std::distance(first, last));
	output.reset();
}

template <typename Input, typename Output>
static void decrypt_using_filter(Input first, Input last, Output d_first) {
	const size_t input_size = std::distance(first, last);

	boost::iostreams::filtering_istream input;
	input.push(
		cryptox::create_rotating_filter<
			cryptox::decryptor<cipher_type>
		>(rotation_key_provider(), PERIOD)
	);

	// Ugly, but effective for this test module.
	const char* input_ = (const char*)&(*first);

	input.push(boost::iostreams::array_source(input_, std::distance(first, last)));

	if (std::distance(first, last) > 0)
		boost::iostreams::copy(input, d_first);

	input.reset();
}

// ----------------------------------------------------------------------------

template <typename Input, typename Output>
static Output encrypt_using_direct(Input first, Input last, Output d_first) {
	auto provider = rotation_key_provider();
	const std::size_t period = PERIOD;

	Input itr = first;
	while (itr != last) {
		const std::size_t input_size = std::distance(itr, last);
		const std::size_t chunk_size = std::min(input_size, period);

		const auto secrets = provider();
		d_first = cryptox::encryptor<cipher_type>(
			secrets.key.begin(), secrets.key.end(),
			secrets. iv.begin(), secrets. iv.end()
		)(itr, itr + chunk_size, d_first);

		itr += chunk_size;
	}

	return d_first;
}

template <typename Input, typename Output>
static Output decrypt_using_direct(Input first, Input last, Output d_first) {
	auto provider = rotation_key_provider();
	const std::size_t period = PERIOD;

	std::auto_ptr<
		cryptox::decryptor<cipher_type>
	> decryptor;

	const auto secrets = provider();
	decryptor.reset(new cryptox::decryptor<cipher_type>(
		secrets.key.begin(), secrets.key.end(),
		secrets. iv.begin(), secrets. iv.end()
	));

	Input itr = first;
	while (itr != last) {
		// FIXME: Only consuming one block at a time.
		const std::size_t input_size = std::distance(itr, last);
		const std::size_t chunk_size = cipher_type::block_size();

		// Must have full blocks.
		BOOST_REQUIRE(input_size >= chunk_size);
		BOOST_REQUIRE(chunk_size % cipher_type::block_size() == 0);

		d_first = decryptor->update(itr, itr + chunk_size, d_first);
		itr += chunk_size;

		if (decryptor->total_output() == period) {
			d_first = decryptor->finalize(d_first);

			const auto secrets = provider();
			decryptor.reset(new cryptox::decryptor<cipher_type>(
				secrets.key.begin(), secrets.key.end(),
				secrets. iv.begin(), secrets. iv.end()
			));
		}
	}

	// Done. Write last bytes.
	d_first = decryptor->finalize(d_first);
	return d_first;
}

// ----------------------------------------------------------------------------

template <typename Input, typename Output>
static Output perform_encryptions(Input first, Input last, Output d_first) {
	std::vector<std::uint8_t> filter;
	std::vector<std::uint8_t> direct;

	encrypt_using_filter(first, last, std::back_inserter(filter));
	encrypt_using_direct(first, last, std::back_inserter(direct));

	BOOST_CHECK_EQUAL_COLLECTIONS(filter.begin(), filter.end(),
	                              direct.begin(), direct.end());

	return std::copy(filter.begin(), filter.end(), d_first);
}

template <typename Input, typename Output>
static Output perform_decryptions(Input first, Input last, Output d_first) {
	std::vector<std::uint8_t> filter;
	std::vector<std::uint8_t> direct;

	decrypt_using_filter(first, last, std::back_inserter(filter));
	decrypt_using_direct(first, last, std::back_inserter(direct));

	BOOST_CHECK_EQUAL_COLLECTIONS(filter.begin(), filter.end(),
	                              direct.begin(), direct.end());

	return std::copy(filter.begin(), filter.end(), d_first);
}

// ----------------------------------------------------------------------------

template <typename Input>
static void roundtrip_test(Input first, Input last) {
	std::vector<std::uint8_t> encrypted;
	std::vector<std::uint8_t> decrypted;

	perform_encryptions(first,             last,            std::back_inserter(encrypted));
	perform_decryptions(encrypted.begin(), encrypted.end(), std::back_inserter(decrypted));

	BOOST_CHECK_EQUAL_COLLECTIONS(first, last, decrypted.begin(), decrypted.end());
}

BOOST_AUTO_TEST_CASE(rotating_endec_filter_test) {
	std::vector<std::uint8_t> input = cryptox::detail::make_random_vector(16*1024);

	//
	// Slice input and test along...
	//
	const size_t initial = 0;
	size_t increment = 1;
	for (size_t i=initial; i<input.size(); i+=increment)
		roundtrip_test(input.begin(), input.begin() + i);
}
