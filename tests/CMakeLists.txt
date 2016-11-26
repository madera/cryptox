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

find_package(Boost COMPONENTS test_exec_monitor REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

if (APPLE)
	# Apple issues unfair deprecation warnings.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -std=c++03")
endif()

add_subdirectory(core)
