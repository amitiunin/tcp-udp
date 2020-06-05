cmake_minimum_required(VERSION 3.16)
project(test_assignment)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(src)

find_package(Threads REQUIRED)

option(WITH_TESTS "Build tests" OFF)
if (WITH_TESTS)
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(tests)
endif ()
