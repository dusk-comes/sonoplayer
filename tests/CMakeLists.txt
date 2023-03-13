find_package(Catch2 3 REQUIRED)
set(TEST_TARGET "tests")

include(Catch)

add_executable(${TEST_TARGET}
    test_soundfile.cpp)

target_link_libraries(${TEST_TARGET}
    PRIVATE Src
    PRIVATE Catch2::Catch2WithMain)

add_test(NAME All COMMAND ${TEST_TARGET}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

#need to run a test with tag "[exp]" for a new feature
#running catch binary produces convenient output
add_custom_target(exp
    COMMAND ${TEST_TARGET} [exp]
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${TEST_TARGET})
