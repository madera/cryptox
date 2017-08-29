# [===========================================================================]
# [                               C r y p t o x                               ]
# [---------------------------------------------------------------------------]
# [                                                                           ]
# [                          Copyright (C) 2016-2017                          ]
# [                      Rodrigo Madera <madera@acm.org>                      ]
# [                                                                           ]
# [---------------------------------------------------------------------------]
# [         Distributed under the Boost Software License, Version 1.0         ]
# [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
# [===========================================================================]

include_directories(.)
include_directories(${Boost_INCLUDE_DIR})
add_executable(core_benchmarks
	main.cxx
	cryptox/message_digests/digest_benchmark.cxx
	cryptox/message_digests/hash_benchmark.cxx
)

target_link_libraries(
	core_benchmarks
	${Boost_LIBRARIES}
	${OPENSSL_LIBRARIES}
)
