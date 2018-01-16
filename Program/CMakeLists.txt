
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h*")

add_executable(PSZT_NEURAL_NETWORK ${SOURCES} ${HEADERS})

file(COPY ${PROJECT_SOURCE_DIR}/Program/manual.txt
        DESTINATION ${PROJECT_BINARY_DIR}/Program/ )


if (Boost_FOUND)
    target_link_libraries(PSZT_NEURAL_NETWORK ${Boost_LIBRARIES})
endif ()