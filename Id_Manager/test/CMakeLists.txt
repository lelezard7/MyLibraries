cmake_minimum_required(VERSION 3.5)
project(IdManagerTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(IdManagerTest src/IdManagerTest.cpp)

target_include_directories(IdManagerTest PRIVATE ../include/)
target_include_directories(IdManagerTest PRIVATE ../../lib/GoogleTest/include/)

target_link_directories(IdManagerTest PRIVATE ../../lib/GoogleTest/)

target_link_libraries(IdManagerTest PRIVATE gtest_main)
target_link_libraries(IdManagerTest PRIVATE gtest)
target_link_libraries(IdManagerTest PRIVATE pthread)
