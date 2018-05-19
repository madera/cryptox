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
#include <cryptox/detail/make_random_string.hxx>
#include <cryptox/message_digests/digest.hxx>
using namespace cryptox;

#define MESSAGE_DIGEST_BENCHMARK_RUN(algorithm, length)                        \
	NONIUS_BENCHMARK(#algorithm "_digest_benchmark",                       \
		[](nonius::chronometer meter) {                                \
			const auto input = detail::make_random_string(length); \
			meter.measure([=] {                                    \
				return digest<algorithm>(input);               \
			});                                                    \
		})

#define MESSAGE_DIGEST_BENCHMARK(algorithm) \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm, 16*1024*1024);

#define MESSAGE_DIGEST_MANIFEST_TEST(algorithm, bits, description) \
	MESSAGE_DIGEST_BENCHMARK(algorithm)

CRYPTOX_PP_FOR_EACH_MESSAGE_DIGEST_ALGORITHM(MESSAGE_DIGEST_MANIFEST_TEST)
