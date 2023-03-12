cmake_minimum_required(VERSION 3.10)

project(sonoplayer)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(ENABLE_TESTS "to add tests to the project" ON)

include(GNUInstallDirs)
include(CheckIncludeFileCXX)
include_directories(${PROJECT_SOURCE_DIR}/include)

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")


if(MSVC)
    add_compile_options(-W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set_property(GLOBAL PROPERTY CXX_STANDARD 17)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)



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

link_libraries(sndfile stdc++fs)



add_subdirectory(src)

if(ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif(ENABLE_TESTS)
