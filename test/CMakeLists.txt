#   === Базовая настройка ===
cmake_minimum_required(VERSION 3.5)
project(ONF_Tests LANGUAGES C CXX)

if(ONF_BUILD_TP_LIB)
    add_subdirectory("../lib/GoogleTest 1.11.0" "${CMAKE_BINARY_DIR}/lib/GoogleTest 1.11.0")
endif()

#   === Включение каталогов ===
include_directories(../include/)
include_directories("../lib/GoogleTest 1.11.0/googletest/include")

#link_directories("${CMAKE_BINARY_DIR}/bin")

#   === Линковка библиотек ===
link_libraries(gtest_main)
link_libraries(gtest)

if(UNIX)
    link_libraries(pthread)
endif()

#   === Тесты ===
add_executable(Common_Test IdManagement/CommonTest.cpp)
add_executable(IdRange_Test IdManagement/IdRangeTest.cpp)
add_executable(IdContainer_Test IdManagement/IdContainerTest.cpp)
add_executable(RangeIdManager_Test IdManagement/RangeIdManagerTest.cpp)

add_executable(ConsoleConstructor_Test ConsoleConstructor/ConsoleConstructorTest.cpp)
