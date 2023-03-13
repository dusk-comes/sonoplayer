add_library(fftw3 SHARED IMPORTED)

find_library(FFTW_LIB_PATH 
    NAMES fftw3
    HINTS ${LIBDIR})
if(NOT FFTW_LIB_PATH)
    message(FATAL_ERROR "libfftw3.so wasn't found")
endif()

target_include_directories(fftw3 INTERFACE ${OLDINCLUDEDIR})
CHECK_INCLUDE_FILE_CXX("fftw3.h" FFTW_HEADER_FOUND)
if (NOT FFTW_HEADER_FOUND)
    message(FATAL_ERROR "fftw3.h wasn't found")
endif()

set_target_properties(fftw3 PROPERTIES
    IMPORTED_LOCATION ${FFTW_LIB_PATH})

link_libraries(fftw3)
