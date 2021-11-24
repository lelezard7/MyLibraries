#   === Базовая настройка ===
cmake_minimum_required(VERSION 3.5)
project(ONF LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#   === Установка и настройка опций ===
option(ONF_ALL_OPTIONS "Выбрать все опции" OFF)
option(ONF_BUILD_TP_LIB "Построить сторонние библиотеки" OFF)
option(ONF_BUILD_TESTS "Построить тесты" OFF)

if(ONF_ALL_OPTIONS)
    set(ONF_BUILD_TP_LIB ON)
    set(ONF_BUILD_TESTS ON)
endif()

include_directories(include)


#   === Добавление подкаталогов сторонних библиотек ===
#if(ONF_BUILD_TP_LIB)
#    add_subdirectory("lib/PDCurses 3.9 CMake")
#endif()

#link_directories("build/qt/debug/lib/PDCurses 3.9 CMake")

#link_libraries(PDc)
#include_directories("lib/PDCurses 3.9 CMake")

#   === Создание библиотеки ===
set(BUILD_SHARED_LIBS ON)

add_library(ONF SHARED
#    src/ConsoleConstructor.cpp
    src/test.cpp

    include/ONF.h
    include/VersionNames.h
    include/IdManagement.h
#    include/ConsoleConstructor.h
    include/EditingStrings.h
    include/Stylesheet.h
    include/UniversalDefinitions.h

    include/IdManagement/IdRange.inl
    include/IdManagement/IdContainer.inl
    include/IdManagement/RangeIdManager.inl
    include/EditingStrings/EditingStrings.inl
    include/Stylesheet/Stylesheet.inl
    include/TypePairs.inl)

#add_dependencies(ONF PDc)



#   === Построение тестов ===
if(ONF_BUILD_TESTS)
    add_subdirectory("test")

    enable_testing()

    add_test(NAME CommonTest COMMAND Common_Test)
endif()
