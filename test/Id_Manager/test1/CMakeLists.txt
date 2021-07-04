cmake_minimum_required(VERSION 3.5)
project(test1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test1 test1.cpp)

target_include_directories(test1 PRIVATE ../../../Id_Manager)
target_include_directories(test1 PRIVATE ../../lib/include/)

target_link_directories(test1 PRIVATE ../../lib/)


target_link_libraries(test1 PRIVATE gtest_main)
target_link_libraries(test1 PRIVATE gtest)
target_link_libraries(test1 PRIVATE pthread)

