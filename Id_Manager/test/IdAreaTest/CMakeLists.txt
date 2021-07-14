cmake_minimum_required(VERSION 3.5)
project(IdAreaTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(IdAreaTest src/IdAreaTest.cpp)

target_include_directories(IdAreaTest PRIVATE ../../include/)
target_include_directories(IdAreaTest PRIVATE ../../../lib/GoogleTest/include/)

target_link_directories(IdAreaTest PRIVATE ../../../lib/GoogleTest/)

target_link_libraries(IdAreaTest PRIVATE gtest_main)
target_link_libraries(IdAreaTest PRIVATE gtest)
target_link_libraries(IdAreaTest PRIVATE pthread)

