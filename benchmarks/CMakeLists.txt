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

find_package(Boost COMPONENTS test_exec_monitor REQUIRED)
find_package(OpenSSL REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (APPLE)
	# Apple issues unfair deprecation warnings.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

include_directories(3rd-party/nonius/include)
add_subdirectory(core)
