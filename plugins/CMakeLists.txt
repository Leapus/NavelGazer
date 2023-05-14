cmake_minimum_required(VERSION 3.18)
project(plugins)

add_subdirectory(sshtransport)
include_directories(../libnavelapi/include ../libnavel/include)
