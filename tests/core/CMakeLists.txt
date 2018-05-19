# [===========================================================================]
# [                               C r y p t o x                               ]
# [---------------------------------------------------------------------------]
# [                                                                           ]
# [                          Copyright (C) 2016-2018                          ]
# [                      Rodrigo Madera <madera@acm.org>                      ]
# [                                                                           ]
# [---------------------------------------------------------------------------]
# [         Distributed under the Boost Software License, Version 1.0         ]
# [ Read accompanying LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt ]
# [===========================================================================]

include_directories(.)

add_executable(core_tests
	main.cxx

	cryptox/detail/to_base64_test.cxx
	cryptox/detail/to_hex_test.cxx
	cryptox/detail/randomize_test.cxx
	cryptox/detail/make_random_string_test.cxx
	cryptox/detail/make_random_vector_test.cxx

	cryptox/block_test.cxx

	cryptox/message_digests/manifest_test.cxx
	cryptox/message_digests/basic_message_digester_test.cxx
	cryptox/message_digests/digest_test.cxx

	cryptox/key_derivation/pbkdf2_test.cxx

	cryptox/symmetric/manifest_test.cxx
	cryptox/symmetric/basic_endec_test.cxx
	cryptox/symmetric/linear_roundtrip_test.cxx
	cryptox/symmetric/quadratic_roundtrip_test.cxx
)

set_property(TARGET core_tests PROPERTY CXX_STANDARD 11)

target_link_libraries(
	core_tests
	${Boost_LIBRARIES}
	${OPENSSL_LIBRARIES}
)

add_test(core_tests core_tests)
