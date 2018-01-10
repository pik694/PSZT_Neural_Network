cmake_minimum_required(VERSION 3.9.3)
project(PSZT_Neural_Network CXX)

set(CMAKE_CXX_STANDARD 14)
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "-lpthread ")
endif ()

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-O3 -Wall -Wextra")

include(CTest)
enable_testing()

set(Project_VERSION_MAJOR 0)
set(Project_VERSION_MINOR 9)

configure_file(
        "${PROJECT_SOURCE_DIR}/Program/program_version"
        "${PROJECT_BINARY_DIR}/Program/program_version.h"
)

find_package(Boost COMPONENTS system timer unit_test_framework program_options REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INDLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    set(ENABLE_TESTS_AT_EACH_BUILD ON) # to disable switch to OFF
endif()


include_directories(${PROJECT_SOURCE_DIR}/Program/sources)
include_directories(${PROJECT_BINARY_DIR}/Program)

add_subdirectory(Program)

add_subdirectory(Tests)










