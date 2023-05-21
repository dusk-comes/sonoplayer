find_package(Catch2 3 REQUIRED)
set(TEST_TARGET "tests")
set(GNUPLOT_SCRIPT "resources/spectral-map.gnuplot")

include(Catch)

add_executable(${TEST_TARGET}
    test_spectrogram.cpp
    test_spectr.cpp
    test_window.cpp
    test_soundfile.cpp)

target_link_libraries(${TEST_TARGET}
    PRIVATE Src
    PRIVATE Catch2::Catch2WithMain)

add_custom_target(gnuplot
    COMMAND ${CMAKE_BINARY_DIR}/${GNUPLOT_SCRIPT} ${CMAKE_BINARY_DIR}/spectral_chirp.dat
    COMMAND ${CMAKE_BINARY_DIR}/${GNUPLOT_SCRIPT} ${CMAKE_BINARY_DIR}/spectral_chirp_overlaps.dat
    DEPENDS ${TEST_TARGET})

#[[TODO HASH COMPARISON
execute_process(COMMAND ${CMAKE_COMMAND} -E compare_files <file1> <file2>
                 RESULT_VARIABLE compare_result)
if( compare_result EQUAL 0)
    message("The files are identical.")
elseif( compare_result EQUAL 1)
    message("The files are different.")
else()
    message("Error while comparing the files.")
endif()]]

add_test(NAME soundfile COMMAND ${TEST_TARGET} "SOUNDFILE*"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME window COMMAND ${TEST_TARGET} "*WINDOW"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME spectr COMMAND ${TEST_TARGET} "SPECTR OF*"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME spectrogram COMMAND ${TEST_TARGET} "SPECTROGRAM"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

add_test(NAME create_png
    COMMAND ${CMAKE_COMMAND} --build . --target gnuplot
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

#need to run a test with tag "[exp]" for a new feature
#running catch binary produces convenient output
add_custom_target(exp
    COMMAND ${TEST_TARGET} [exp]
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    DEPENDS ${TEST_TARGET})
