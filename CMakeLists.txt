cmake_minimum_required(VERSION 3.5)

project(dtr LANGUAGES CXX)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

find_library(LIBRT rt)

#
# LIBRARY
#

add_library(dtr INTERFACE)

target_include_directories(dtr INTERFACE include Boost::boost)


#
# TEST
#

add_executable(test test/test.cpp)

target_link_libraries(test dtr Threads::Threads ${LIBRT})

set_target_properties(test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
  target_compile_options(test PRIVATE /W4 /WX)
else()
  target_compile_options(test PRIVATE -Wall -Wextra -pedantic -Werror -Weffc++)
endif()
