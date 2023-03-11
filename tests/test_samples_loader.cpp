#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include "samples_loader.hpp"

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
