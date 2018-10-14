cmake_minimum_required(VERSION 3.5)
project(Aho-Corasick-project)


set(HEADERS ac/ac.h)


set(SRCS
        src/DebugLog.cpp
        src/trie.cpp
        src/ac.cpp
        )


include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR})

add_library(ac ${SRCS} ${HEADERS})



find_package(PkgConfig REQUIRED)
pkg_check_modules(GoogleTest gtest gtest_main)
if (GoogleTest_FOUND)
    include_directories(${GoogleTest_INCLUDE_DIRS})
    add_subdirectory(tests)
endif (GoogleTest_FOUND)