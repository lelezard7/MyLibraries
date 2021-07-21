cmake_minimum_required(VERSION 3.5)
project(IdManagerTest LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_subdirectory("../../lib/GoogleTest 1.11.0" CMAKE_CURRENT_BINARY_DIR)

add_executable(IdManagerTest IdManagerTest.cpp)

target_include_directories(IdManagerTest PRIVATE ../../include/)
target_include_directories(IdManagerTest PRIVATE "../../lib/GoogleTest 1.11.0/googletest/include")
target_include_directories(IdManagerTest PRIVATE "../../lib/GoogleTest 1.11.0/googlemock/include")

target_link_libraries(IdManagerTest PRIVATE gtest_main)
target_link_libraries(IdManagerTest PRIVATE gtest)

if(UNIX)
    target_link_libraries(IdManagerTest PRIVATE pthread)
endif()
