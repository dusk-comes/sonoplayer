find_package(Catch2 3 REQUIRED)
set(TEST_TARGET "tests")

include(Catch)
include(CTest)

add_executable(${TEST_TARGET}
    test_samples_loader.cpp)

target_link_libraries(${TEST_TARGET}
    PRIVATE Src
    PRIVATE Catch2::Catch2WithMain)
