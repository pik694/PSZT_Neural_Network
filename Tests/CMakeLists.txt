

if (ENABLE_TESTS_AT_EACH_BUILD)

    file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/Program/sources/*.cpp")
    file(GLOB_RECURSE HEADERS "${PROJECT_SOURCE_DIR}/Program/sources/*.h*")

    set(TEST_SOURCES test_main.cpp NeuralNetworkTests.cpp SerializatorTests.cpp XOR_NNTests.cpp)

    add_executable(Tests ${TEST_SOURCES} ${SOURCE_FILES} ${HEADERS})
    target_link_libraries(Tests ${Boost_LIBRARIES})

    add_test(boostUnitTestsRun Tests)

    if (CMAKE_CONFIGURATION_TYPES)
        add_custom_target(runTests COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure
                --build-config "$<CONFIGURATION>"
                DEPENDS Tests)
    else()
        add_custom_target(runTests COMMAND ${CMAKE_CTEST_COMMAND}
                --force-new-ctest-process --output-on-failure
                DEPENDS Tests)
    endif()


endif()