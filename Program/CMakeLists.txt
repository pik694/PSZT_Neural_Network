
file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h*")

add_executable(PSZT_NEURAL_NETWORK ${SOURCES} ${HEADERS})

target_link_libraries(PSZT_NEURAL_NETWORK ${Boost_Libraries})