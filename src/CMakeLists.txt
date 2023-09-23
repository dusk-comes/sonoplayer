add_library(${PROJECT_NAME}
    fft_routine.cpp
    spectrogram.cpp
    spectrogram_builder.cpp
    data_manager.cpp
    windowing.cpp
    soundfile.cpp)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include)
