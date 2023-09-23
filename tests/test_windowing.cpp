#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "windowing.hpp"
#include <functional>
#include <vector>
#include <iterator>
#include <fstream>
#include <iostream>

using namespace std::placeholders;

class test_windowing
{
    protected:
        SAMPLE_ARRAY expected;
        SAMPLE_ARRAY result;

    public:
        test_windowing(const std::string filename)
        {
            auto numpy_out = std::ifstream("resources/" + filename);
            std::istream_iterator<double> start(numpy_out), end;
            std::move(start, end, std::back_inserter(expected));

            result.resize(expected.size());
            std::fill(result.begin(), result.end(), 1);
        }

        void evaluate(const std::function<void (SAMPLE_ARRAY&)> &func)
        {
            func(result);
            for (std::size_t i = 0; i < expected.size(); ++i)
            {
                REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
            }
        }
};

class test_window_hanning : public test_windowing
{
    public:
        test_window_hanning() : test_windowing("hanning.txt") {}

        void run()
        {
            test_windowing::evaluate(std::bind(windowing::hanning, _1));
        }
};

class test_window_hamming : public test_windowing
{
    public:
        test_window_hamming() : test_windowing("hamming.txt") {}

        void run()
        {
            test_windowing::evaluate(std::bind(windowing::hamming, _1));
        }
};

class test_window_blackman : public test_windowing
{
    public:
        test_window_blackman() : test_windowing("blackman.txt") {}

        void run()
        {
            test_windowing::evaluate(std::bind(windowing::blackman, _1));
        }
};

class test_window_flattop : public test_windowing
{
    public:
        test_window_flattop() : test_windowing("flattop.txt") {}

        void run()
        {
            test_windowing::evaluate(std::bind(windowing::flattop, _1));
        }
};

METHOD_AS_TEST_CASE(test_window_hanning::run, "HANNING WINDOW")
METHOD_AS_TEST_CASE(test_window_hamming::run, "HAMMING WINDOW")
METHOD_AS_TEST_CASE(test_window_blackman::run, "BLACKMAN WINDOW")
METHOD_AS_TEST_CASE(test_window_flattop::run, "FLATTOP WINDOW")
