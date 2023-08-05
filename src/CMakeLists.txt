add_library(${PROJECT_NAME}
    spectr.cpp
    spectrogram.cpp
    model.cpp
    window.cpp
    soundfile.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)
