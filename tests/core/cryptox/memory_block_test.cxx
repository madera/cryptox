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
#include <cryptox/memory_block.hxx>
using namespace cryptox;

BOOST_AUTO_TEST_CASE(memory_block_test) {
	{
		const char* input = "C string";
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input,         output.first );
		BOOST_CHECK_EQUAL(strlen(input), output.second);
	}
	{
		const char input[] = "Another C string";
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input,         output.first );
		BOOST_CHECK_EQUAL(strlen(input), output.second);
	}
	{
		const char* input = "Sized C string";
		memory_block output = to_memory_block(input, 3);
		BOOST_CHECK_EQUAL(input, output.first );
		BOOST_CHECK_EQUAL(3,     output.second);
	}
	{
		const unsigned char input[] = { 0x00, 0x01, 0x02 };
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input,         output.first );
		BOOST_CHECK_EQUAL(sizeof(input), output.second);
	}
	{
		const unsigned char input[] = { 0x00, 0x01, 0x02 };
		memory_block output = to_memory_block(input, sizeof(input));
		BOOST_CHECK_EQUAL(input,         output.first );
		BOOST_CHECK_EQUAL(sizeof(input), output.second);
	}
	{
		const std::string input = "abcdef";
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input.c_str(), output.first );
		BOOST_CHECK_EQUAL(input.size(),  output.second);
	}
	{
		boost::array<char, 3> input = { 'a', 'b', 'c' };
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input.data(), output.first );
		BOOST_CHECK_EQUAL(input.size(), output.second);
	}
	{
		boost::array<int, 3> input = { 0x00, 0x01, 0x02 };
		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input.data(), output.first );
		BOOST_CHECK_EQUAL(input.size()*sizeof(int), output.second);
	}
	{
		std::vector<char> input;
		input.push_back('a');
		input.push_back('b');
		input.push_back('c');

		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input.data(), output.first );
		BOOST_CHECK_EQUAL(input.size(), output.second);
	}
	{
		std::vector<size_t> input;
		input.push_back(1);
		input.push_back(2);
		input.push_back(3);

		memory_block output = to_memory_block(input);
		BOOST_CHECK_EQUAL(input.data(),                output.first );
		BOOST_CHECK_EQUAL(input.size()*sizeof(size_t), output.second);
	}
}
