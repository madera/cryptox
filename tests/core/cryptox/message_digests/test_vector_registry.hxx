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
#include <cryptox/message_digests/basic_message_digester.hxx>
#include <cryptox/detail/to_hex.hxx>
#include <boost/foreach.hpp>
#include <string>
#include <map>

namespace cryptox { namespace test {

	template <class Algorithm>
	struct test_vector_registry {
		typedef std::map<std::string, std::string> test_vector_map_type;

		static test_vector_map_type& test_vectors() {
			static test_vector_map_type algorithm_test_vectors;
			return algorithm_test_vectors;
		}

		static void test_all_vectors() {
			// TODO: Have a warning on untested algorithms.

			BOOST_FOREACH(test_vector_map_type::value_type& pair, test_vectors()) {
				const std::string& input    = pair.first;
				const std::string& expected = pair.second;
				std::string actual;

				basic_message_digester<Algorithm> digester;
				digester(input.begin(), input.end(), std::back_inserter(actual));

				BOOST_CHECK_EQUAL(to_hex(actual), expected);
			}
		}

		test_vector_registry(const std::string input, const std::string expected) {
			test_vectors()[input] = expected;
		}
	};

}}

#define CRYPTOX_MESSAGE_DIGEST_TEST_VECTOR(algorithm, input, expected) \
	cryptox::test::test_vector_registry<algorithm> \
	BOOST_PP_CAT(test_vector_registry_##algorithm##_,__LINE__)(input, expected);
