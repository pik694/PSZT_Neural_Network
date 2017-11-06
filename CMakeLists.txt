cmake_minimum_required(VERSION 3.9.3)
project(PSZT_test)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(PSZT_test ${SOURCE_FILES})


find_package(Boost 1.65.1 EXACT REQUIRED COMPONENTS system timer)

if (Boost_FOUND)
    include_directories(${Boost_INDLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(PSZT_test ${Boost_LIBRARIES})
endif()





