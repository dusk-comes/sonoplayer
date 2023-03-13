set(APP_TARGET ${CMAKE_PROJECT_NAME})

add_library(Src
    soundfile.cpp)

add_executable(${APP_TARGET} main.cpp)

target_link_libraries(${APP_TARGET} Src)
