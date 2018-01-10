
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h*")

add_executable(PSZT_NEURAL_NETWORK ${SOURCES} ${HEADERS})

if (Boost_FOUND)
    target_link_libraries(PSZT_NEURAL_NETWORK ${Boost_LIBRARIES})
endif ()