cmake_minimum_required(VERSION 3.5)
project(Aho-Corasick-project)

set(CMAKE_CXX_STANDARD 11)

set(HEADERS ahocorasick/ahocorasick.h)


set(SRCS
        src/DebugLog.cpp
        src/Node.cpp
        src/ahocorasick.cpp
        )


include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR})

add_library(ahocorasick ${SRCS} ${HEADERS})


find_package(PkgConfig REQUIRED)
pkg_check_modules(GoogleTest gtest gtest_main)
if (GoogleTest_FOUND)
    include_directories(${GoogleTest_INCLUDE_DIRS})
    set(LIBS
            ${LIBS} ${GoogleTest_LIBRARIES} pthread)
    add_subdirectory(tests)
endif (GoogleTest_FOUND)