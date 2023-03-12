#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "samples_loader.hpp"
#include <cmath>

TEST_CASE("get file's metadata")
{
    samples_loader file("resources/test.wav");

    REQUIRE(file.samplerate() == 44100);
    REQUIRE(file.channels() == 1);
}

TEST_CASE("try to open a not existed file")
{
    REQUIRE_THROWS_AS(samples_loader("foo.bar"), std::ios_base::failure);
    REQUIRE_THROWS_WITH(samples_loader("foo.bar"), "filename foo.bar not exists: iostream error");
}

TEST_CASE("read samples")
{
    samples_loader file("resources/test.wav");
    auto total_count_samples = file.frames() * file.channels();
    auto expected_count_block = (std::size_t) std::ceil( (double) total_count_samples / BUFFER_SIZE);

    std::size_t count_block = 0;
    std::size_t dummy = 0;
    do
    {
        [[maybe_unused]] auto [data, frames] = file.receive();
        dummy = frames;
        if(frames) ++count_block;
    }
    while (dummy > 0);

    REQUIRE(expected_count_block == count_block);
}
