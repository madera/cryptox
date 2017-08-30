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

add_executable(core_tests
	main.cxx
	cryptox/all_test.cxx
	cryptox/detail/hex_string_test.cxx
	cryptox/block_test.cxx
	cryptox/block_view_test.cxx
	cryptox/message_digests/all_test.cxx
	cryptox/message_digests/digest_test.cxx
	cryptox/message_digests/hash_test.cxx
	cryptox/key_derivation/pbkdf2_test.cxx
)

target_link_libraries(
	core_tests
	${Boost_LIBRARIES}
	${OPENSSL_LIBRARIES}
)

add_test(core_tests core_tests)
