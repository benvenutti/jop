set(TEST_NAME jvp-tests)

add_executable( ${TEST_NAME}
        jvp/catch.config.cpp
        jvp/Parser.identifier.test )

target_link_libraries( ${TEST_NAME} PRIVATE catch2 jvp )

add_test( NAME jvp-test-suite COMMAND ${TEST_NAME} )
