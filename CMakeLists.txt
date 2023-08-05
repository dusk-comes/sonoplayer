cmake_minimum_required(VERSION 3.10)

project(sonoplayer LANGUAGES CXX)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TESTS "to add tests to the project" ON)
option(STATIC_CODE_ANALYSIS OFF)
if(STATIC_CODE_ANALYSIS)
    find_program(TIDY_APP NAMES clang-tidy clang-tidy-13 clang-tidy-14 clang-tidy-15)
    set(CMAKE_CXX_CLANG_TIDY ${TIDY_APP} --config-file=${PROJECT_SOURCE_DIR}/.clang-tidy)
endif()

include(GNUInstallDirs)
include(CheckIncludeFileCXX)
include(libsndfile.cmake)                                   # external linked library
include(fftw.cmake)                                         # external linked library
include_directories(${PROJECT_SOURCE_DIR}/include)

file(COPY "resources" DESTINATION "${CMAKE_BINARY_DIR}")

if(MSVC)
    add_compile_options(-W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

link_libraries(stdc++fs)

add_subdirectory(src)

if(ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif(ENABLE_TESTS)
