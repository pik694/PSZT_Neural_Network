cmake_minimum_required(VERSION 3.9.3)
project(PSZT_Neural_Network CXX)

set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

SET(BOOST_ROOT "/usr/local/boost_1_65_1")

find_package(Boost 1.65.1 EXACT COMPONENTS system timer unit_test_framework REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INDLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    set(ENABLE_TESTS_AT_EACH_BUILD ON) # to disable switch to OFF
endif()


include_directories(Program/sources)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Program)

#add_subdirectory(Tests)










