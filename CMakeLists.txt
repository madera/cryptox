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

cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

enable_testing()
project(cryptox CXX)

include_directories(include)
add_subdirectory(tests)
