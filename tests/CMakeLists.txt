find_package(Catch2 3 REQUIRED)
set(TEST_TARGET "tests")

include(Catch)

add_executable(${TEST_TARGET}
    test_spectrogram.cpp
    test_spectr.cpp
    test_window.cpp
    test_soundfile.cpp)

target_link_libraries(${TEST_TARGET}
    PRIVATE Src
    PRIVATE Catch2::Catch2WithMain)

add_test(NAME soundfile COMMAND ${TEST_TARGET} "SOUNDFILE*"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME window COMMAND ${TEST_TARGET} "*WINDOW"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME spectr COMMAND ${TEST_TARGET} "SPECTR*"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

#need to run a test with tag "[exp]" for a new feature
#running catch binary produces convenient output
add_custom_target(exp
    COMMAND ${TEST_TARGET} [exp]
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${TEST_TARGET})
