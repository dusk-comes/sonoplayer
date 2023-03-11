set(APP_TARGET ${CMAKE_PROJECT_NAME})

add_library(Src
    samples_loader.cpp)

add_executable(${APP_TARGET} main.cpp)

target_link_libraries(${APP_TARGET} Src)
