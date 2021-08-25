cmake_minimum_required(VERSION 3.5)
project(ONF LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS ON)

add_library(ONF SHARED
                src/XmlSave/XmlFilter.cpp
                src/XmlSave/TagStructure.cpp
                src/XmlSave/SaveModule.cpp

                src/ConsShell/Console_IO.cpp
                src/ConsShell/Console_Input.cpp
                src/ConsShell/Console_Editor.cpp
                src/ConsShell/Console_Output.cpp

                include/XmlSave/TagStructure.h
                include/XmlSave/XmlFilter.h
                include/XmlSave/SaveModule.h

                include/IdManagement/IdContainer.inl
                include/IdManagement/IdRange.inl
                include/IdManagement/RangeIdManager.inl

                include/ONF.h
                include/Console_IO.h
                include/VersionNames.h
                include/IdManagement.h)
