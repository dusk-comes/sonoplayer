#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/catch_approx.hpp>
#include "window.hpp"
#include <vector>
#include <iterator>
#include <fstream>

TEST_CASE("HANNING WINDOW")
{
    auto numpy_out = std::ifstream("resources/hanning.txt"); 
    std::istream_iterator<double> start(numpy_out), end;
    std::vector<double> expected(start, end);

    std::vector<double> result = window::hanning(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
    }
}

TEST_CASE("HAMMING WINDOW")
{
    auto numpy_out = std::ifstream("resources/hamming.txt"); 
    std::istream_iterator<double> start(numpy_out), end;
    std::vector<double> expected(start, end);

    std::vector<double> result = window::hamming(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
    }
}

TEST_CASE("BLACKMAN WINDOW")
{
    auto numpy_out = std::ifstream("resources/blackman.txt"); 
    std::istream_iterator<double> start(numpy_out), end;
    std::vector<double> expected(start, end);

    std::vector<double> result = window::blackman(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
    }
}

TEST_CASE("FLATTOP WINDOW")
{
    auto numpy_out = std::ifstream("resources/flattop.txt"); 
    std::istream_iterator<double> start(numpy_out), end;
    std::vector<double> expected(start, end);

    std::vector<double> result = window::flattop(expected.size());
    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
    }
}
