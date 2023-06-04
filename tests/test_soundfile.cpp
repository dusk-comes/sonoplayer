#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "soundfile.hpp"
#include <cmath>
#include <array>

TEST_CASE("SOUNDFILE TO READ METADATA")
{
    soundfile file("resources/test.wav");

    REQUIRE(file.samplerate() == 44100);
    REQUIRE(file.channels() == 1);
}

TEST_CASE("SOUNDFILE TO READ SAMPLES")
{
    soundfile file("resources/test.wav");
    auto total_count_samples = file.frames() * file.channels();

    #define BUFFER_SIZE 1024
    auto expected_count_block = (std::size_t) std::ceil( (double) total_count_samples / BUFFER_SIZE);

    std::size_t count_block = 0;
    SAMPLE_ARRAY buf(BUFFER_SIZE);
    while (file.load_data(buf))
    {
        ++count_block;
    }

    REQUIRE(expected_count_block == count_block);
}
