# [===========================================================================]
# [                               C r y p t o x                               ]
# [---------------------------------------------------------------------------]
# [                                                                           ]
# [                          Copyright (C) 2016-2017                          ]
# [                      Rodrigo Madera <madera@acm.org>                      ]
# [                                                                           ]
# [---------------------------------------------------------------------------]
# [                            All Rights Reserved                            ]
# [===========================================================================]

include_directories(.)

add_executable(core_tests
	main.cxx
	cryptox/message_digest_test.cxx
	cryptox/hex_string_test.cxx
	cryptox/hash_test.cxx
)

target_link_libraries(
	core_tests
	crypto
	${Boost_LIBRARIES}
)

add_test(core_tests core_tests)
