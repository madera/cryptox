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
#include <cryptox/message_digests/digest.hxx>
#include <cryptox/detail/make_random_string.hxx>
using namespace cryptox;

#define MESSAGE_DIGEST_BENCHMARK_RUN(algorithm, input_length) \
	NONIUS_BENCHMARK(#input_length "_" #algorithm "_hash_benchmark", \
		[](nonius::chronometer meter) { \
			const std::string input = detail::make_random_string(input_length); \
			meter.measure([=] { \
				return digest<algorithm>(input); \
			}); \
		})

#define MESSAGE_DIGEST_BENCHMARK(algorithm) \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm,   16); \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm,   64); \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm,  256); \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm, 1024); \
	MESSAGE_DIGEST_BENCHMARK_RUN(algorithm, 8192);

MESSAGE_DIGEST_BENCHMARK(md5);
MESSAGE_DIGEST_BENCHMARK(sha);
MESSAGE_DIGEST_BENCHMARK(sha1);
MESSAGE_DIGEST_BENCHMARK(sha224);
MESSAGE_DIGEST_BENCHMARK(sha256);
MESSAGE_DIGEST_BENCHMARK(sha384);
MESSAGE_DIGEST_BENCHMARK(sha512);
