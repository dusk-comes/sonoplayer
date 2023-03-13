cmake_minimum_required(VERSION 3.10)

project(sonoplayer)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
option(ENABLE_TESTS "to add tests to the project" ON)

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
