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

add_executable(test-dtr test/test.cpp)

target_link_libraries(test-dtr dtr Threads::Threads ${LIBRT})

set_target_properties(test-dtr PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

if(MSVC)
  target_compile_options(test-dtr PRIVATE /W4 /WX)
else()
  target_compile_options(test-dtr PRIVATE -Wall -Wextra -pedantic -Werror -Weffc++)
endif()


install(TARGETS dtr test-dtr)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/dtr DESTINATION include)

