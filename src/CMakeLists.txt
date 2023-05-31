set(APP_TARGET ${CMAKE_PROJECT_NAME})

add_library(Src
    spectr.cpp
    spectrogram.cpp
    window.cpp
    soundfile.cpp)

add_executable(${APP_TARGET} main.cpp)

target_link_libraries(${APP_TARGET} Src)
