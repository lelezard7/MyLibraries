cmake_minimum_required(VERSION 3.5)
project(IdsContainerTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(IdsContainerTest src/IdsContainerTest.cpp)

target_include_directories(IdsContainerTest PRIVATE ../../include/)
target_include_directories(IdsContainerTest PRIVATE ../../../lib/GoogleTest/include/)

target_link_directories(IdsContainerTest PRIVATE ../../../lib/GoogleTest/)

target_link_libraries(IdsContainerTest PRIVATE gtest_main)
target_link_libraries(IdsContainerTest PRIVATE gtest)
target_link_libraries(IdsContainerTest PRIVATE pthread)

