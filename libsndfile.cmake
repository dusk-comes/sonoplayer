add_library(sndfile SHARED IMPORTED)

find_library(SOUND_FILE_LIB_PATH 
    NAMES sndfile
    HINTS ${LIBDIR})
if(NOT SOUND_FILE_LIB_PATH)
    message(FATAL_ERROR "libsndfile.so wasn't found")
endif()

target_include_directories(sndfile INTERFACE ${OLDINCLUDEDIR})
CHECK_INCLUDE_FILE_CXX("sndfile.hh" SOUND_FILE_HEADER_FOUND)
if (NOT SOUND_FILE_HEADER_FOUND)
    message(FATAL_ERROR "sndfile.hh wasn't found")
endif()

set_target_properties(sndfile PROPERTIES
    IMPORTED_LOCATION ${SOUND_FILE_LIB_PATH})

link_libraries(sndfile)
