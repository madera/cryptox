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
#include <cryptox/detail/make_random_vector.hxx>
#include <boost/foreach.hpp>

BOOST_AUTO_TEST_CASE(nonrepeat_make_random_vector_test) {
	typedef std::vector<std::uint8_t> buffer_type;
	buffer_type buffers[128];

	BOOST_FOREACH(buffer_type& buffer, buffers) {
		buffer = cryptox::detail::make_random_vector();
	}

	// Scan O(n^2) for duplicates.
	BOOST_FOREACH(const buffer_type& buffer, buffers) {
		size_t instances = 0;

		BOOST_FOREACH(const buffer_type& other, buffers) {
			if (buffer == other)
				++instances;
		}

		// We should only have one instance per random buffer.
		BOOST_CHECK_EQUAL(instances, 1);
	}
}
