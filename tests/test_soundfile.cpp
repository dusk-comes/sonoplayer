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

TEST_CASE("SOUNDFILE TO OPEN A NON EXISTING FILE")
{
    REQUIRE_THROWS_AS(soundfile("foo.bar"), std::ios_base::failure);
    REQUIRE_THROWS_WITH(soundfile("foo.bar"), "filename foo.bar not exists: iostream error");
}

TEST_CASE("SOUNDFILE TO READ SAMPLES")
{
    soundfile file("resources/test.wav");
    auto total_count_samples = file.frames() * file.channels();

    #define BUFFER_SIZE 1024
    auto expected_count_block = (std::size_t) std::ceil( (double) total_count_samples / BUFFER_SIZE);

    std::size_t count_block = 0;
    std::array<SAMPLE, BUFFER_SIZE> buf;
    while (file.data(buf.data(), buf.size()))
    {
        ++count_block;
    }

    REQUIRE(expected_count_block == count_block);
}
