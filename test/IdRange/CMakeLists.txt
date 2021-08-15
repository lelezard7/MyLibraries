cmake_minimum_required(VERSION 3.5)
project(IdRangeTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory("../../lib/GoogleTest 1.11.0" CMAKE_CURRENT_BINARY_DIR)

add_executable(IdRangeTest IdRangeTest.cpp)

target_include_directories(IdRangeTest PRIVATE ../../include/)
target_include_directories(IdRangeTest PRIVATE "../../lib/GoogleTest 1.11.0/googletest/include")
target_include_directories(IdRangeTest PRIVATE "../../lib/GoogleTest 1.11.0/googlemock/include")

target_link_libraries(IdRangeTest PRIVATE gtest_main)
target_link_libraries(IdRangeTest PRIVATE gtest)

if(UNIX)
    target_link_libraries(IdRangeTest PRIVATE pthread)
endif()
