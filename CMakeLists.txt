cmake_minimum_required(VERSION 3.10)

project(sonoplayer)
set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(GCC_LIKE_CXX $<$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>:-Wall -Wextra -pedantic -Werror>)

include(GNUInstallDirs)
include(CheckIncludeFileCXX)

add_executable(sonoplayer
    main.cpp)

#IMPORT https://github.com/libsndfile/libsndfile
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
#END TO IMPORT libsndfile

set_target_properties(sonoplayer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

target_compile_options(sonoplayer INTERFACE
    ${GCC_LIKE_CXX})

target_link_libraries(sonoplayer sndfile)
