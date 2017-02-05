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

#include "pch.hxx"
#include <cryptox/block_view.hxx>
using namespace cryptox;

BOOST_AUTO_TEST_CASE(block_view_test) {
	{
		const char* input = "C string";
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input,         output.data);
		BOOST_CHECK_EQUAL(strlen(input), output.size);
	}
	{
		const char input[] = "Another C string";
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input,         output.data);
		BOOST_CHECK_EQUAL(strlen(input), output.size);
	}
	{
		const char* input = "Sized C string";
		block_view output = to_block_view(input, 3);
		BOOST_CHECK_EQUAL(input, output.data);
		BOOST_CHECK_EQUAL(3,     output.size);
	}
	{
		const unsigned char input[] = { 0x00, 0x01, 0x02 };
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input,         output.data);
		BOOST_CHECK_EQUAL(sizeof(input), output.size);
	}
	{
		const unsigned char input[] = { 0x00, 0x01, 0x02 };
		block_view output = to_block_view(input, sizeof(input));
		BOOST_CHECK_EQUAL(input,         output.data);
		BOOST_CHECK_EQUAL(sizeof(input), output.size);
	}
	{
		const std::string input = "abcdef";
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input.c_str(), output.data);
		BOOST_CHECK_EQUAL(input.size(),  output.size);
	}
	{
		boost::array<char, 3> input = { 'a', 'b', 'c' };
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input.data(), output.data);
		BOOST_CHECK_EQUAL(input.size(), output.size);
	}
	{
		boost::array<int, 3> input = { 0x00, 0x01, 0x02 };
		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input.data(), output.data);
		BOOST_CHECK_EQUAL(input.size()*sizeof(int), output.size);
	}
	{
		std::vector<char> input;
		input.push_back('a');
		input.push_back('b');
		input.push_back('c');

		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input.data(), output.data);
		BOOST_CHECK_EQUAL(input.size(), output.size);
	}
	{
		std::vector<size_t> input;
		input.push_back(1);
		input.push_back(2);
		input.push_back(3);

		block_view output = to_block_view(input);
		BOOST_CHECK_EQUAL(input.data(),                output.data);
		BOOST_CHECK_EQUAL(input.size()*sizeof(size_t), output.size);
	}
}
