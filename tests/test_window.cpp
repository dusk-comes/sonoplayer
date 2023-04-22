#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "window.hpp"
#include <functional>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>

using namespace std::placeholders;

class test_window
{
    protected:
        std::vector<SAMPLE> expected;
        SAMPLE_ARRAY result;

    public:
        test_window(const std::string filename) : result{nullptr}
        {
            auto numpy_out = std::ifstream("resources/" + filename);
            std::istream_iterator<double> start(numpy_out), end;
            std::move(start, end, std::back_inserter(expected));

            SAMPLE_ARRAY tmp(new SAMPLE[expected.size()]);
            std::fill(tmp.get(), tmp.get() + expected.size(), 1);
            result.swap(tmp);
        }

        void evaluate(const std::function<void (const SAMPLE_ARRAY&, const std::size_t)> &func)
        {
            func(result, expected.size());
            for (std::size_t i = 0; i < expected.size(); ++i)
            {
                REQUIRE(expected[i] == Catch::Approx(result[i]).margin(0.000001));
            }
        }
};

class test_window_hanning : public test_window
{
    public:
        test_window_hanning() : test_window("hanning.txt") {}

        void run()
        {
            test_window::evaluate(std::bind(window::hanning, test_window::result, test_window::expected.size()));
        }
};

class test_window_hamming : public test_window
{
    public:
        test_window_hamming() : test_window("hamming.txt") {}

        void run()
        {
            test_window::evaluate(std::bind(window::hamming, test_window::result, test_window::expected.size()));
        }
};

class test_window_blackman : public test_window
{
    public:
        test_window_blackman() : test_window("blackman.txt") {}

        void run()
        {
            test_window::evaluate(std::bind(window::blackman, test_window::result, test_window::expected.size()));
        }
};

class test_window_flattop : public test_window
{
    public:
        test_window_flattop() : test_window("flattop.txt") {}

        void run()
        {
            test_window::evaluate(std::bind(window::flattop, test_window::result, test_window::expected.size()));
        }
};

METHOD_AS_TEST_CASE(test_window_hanning::run, "HANNING WINDOW")
METHOD_AS_TEST_CASE(test_window_hamming::run, "HAMMING WINDOW")
METHOD_AS_TEST_CASE(test_window_blackman::run, "BLACKMAN WINDOW")
METHOD_AS_TEST_CASE(test_window_flattop::run, "FLATTOP WINDOW")
