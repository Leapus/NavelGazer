cmake_minimum_required(VERSION 3.18)
project(NavelGazer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(libnavel/include)

add_subdirectory(libnavel)
add_subdirectory(libnavelpluginapi)
add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(plugins)

add_dependencies(navelpluginapi navel)
add_dependencies(navelservice navel navelpluginapi)
add_dependencies(navelviewer navel navelpluginapi)


