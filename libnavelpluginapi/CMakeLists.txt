cmake_minimum_required(VERSION 3.18)
project(libnavelpluginapi)
include_directories(include ../libnavel/include)

add_library( navelpluginapi SHARED plugin_log.cpp )
target_link_libraries(navelpluginapi navel)

