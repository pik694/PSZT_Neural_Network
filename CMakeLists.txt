cmake_minimum_required(VERSION 3.9.3)
project(PSZT_test)

set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

set(SOURCE_FILES main.cpp SampleClass.cpp SampleClass.hpp)
add_executable(PSZT_test ${SOURCE_FILES})

SET(BOOST_ROOT "/usr/local/boost_1_65_1")
find_package(Boost 1.65.1 EXACT COMPONENTS system timer unit_test_framework REQUIRED)

if (Boost_FOUND)
    include_directories(${Boost_INDLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(PSZT_test ${Boost_LIBRARIES})

    set(ENABLE_TESTS_AT_EACH_BUILD ON) # to disable switch to OFF

endif()

add_subdirectory(Tests)










