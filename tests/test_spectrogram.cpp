#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <numeric>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <fstream>

#include "common.hpp"
#include "spectrogram.hpp"

struct chirp { 
    public:
        double freq_start;
        double freq_end;

        chirp(const std::size_t samples, const double step) :
            freq_start{0},
            freq_end{0},
            y(samples),
            coef(2), 
            initialized(false)
        {
            time_range(step);
        }

        SAMPLE_ARRAY data()
        {
            if (!initialized)
            {
                exec();
                initialized = true;
            }
            return y;
        }

    private:
        SAMPLE_ARRAY y;
        const double coef;
        bool initialized;

        void time_range(const double step)
        {
            std::for_each(y.begin(), y.end(), [point=0., step](auto &value) mutable {
                    value = point;
                    point += step;});
        }

        void exec()
        {
            auto func = [this](auto value) {
                return std::cos(2 * M_PI * value *
                        (freq_start + (freq_end - freq_start) *
                         std::pow(value, 2) / (3 * std::pow(coef, 2))));
            };

            std::transform(y.begin(), y.end(), y.begin(), func);
        }
};

void write_file(const char *filename, const std::vector<std::vector<double>> &vec, const double time_resolution, const double freq_resolution, const std::size_t bins)
{
    std::ofstream file{filename};
    const double time_delta = time_resolution / 2; // take a middle's interval to proect a signal's spectrogram on time axis
    for (std::size_t time_point = 1; time_point < vec.size(); ++time_point)
    {
        for (std::size_t bin = 1; bin < bins; ++bin)
        {
            file << time_delta * static_cast<double>(time_point) << " "
                 << freq_resolution * static_cast<double>(bin) << " "
                 << vec[time_point][bin] << std::endl; 
        }
        file << std::endl;
    }
}

TEST_CASE("SPECTROGRAM")
{
    const double step = 0.001;
    const double samplerate = 1 / step;

    chirp chirp(static_cast<std::size_t>(2 / step), step);
    chirp.freq_start = 50;
    chirp.freq_end = 250;

    std::vector<std::vector<double>> result;
    
    auto fill_result = [&result](SAMPLE_ARRAY magnitude) {
        result.push_back(magnitude);
    };

    spectrogram sg(fill_result);
    sg.segments(128);
    sg.prepare();

    auto expected_bins = sg.bins() + 1; // ftt routine returns DC parts
    SECTION("without overlapping")
    {
        const double time_resolution = sg.sample_resolution() / samplerate;

        sg.calculate(chirp.data());
        write_file("spectral_chirp.dat", result, time_resolution, sg.freq_resolution(samplerate), sg.bins());

        auto expected_segments = chirp.data().size() / sg.segments();
        CHECK(result.size() == expected_segments);
        CHECK(result.front().size() == expected_bins);
        CHECK(result.back().size() == expected_bins);
    }

    SECTION("overlapping segments")
    {
        const std::size_t overlapping_blocks = 120;
        sg.overlapped(overlapping_blocks);
        const double time_resolution = sg.sample_resolution() / samplerate;

        sg.calculate(chirp.data());
        write_file("spectral_chirp_overlaps.dat", result, time_resolution, sg.freq_resolution(samplerate), sg.bins());

        auto expected_segments = (chirp.data().size() - overlapping_blocks) / (sg.segments() - overlapping_blocks);
        CHECK(result.size() == expected_segments);
        CHECK(result.front().size() == expected_bins);
        CHECK(result.back().size() == expected_bins);
    }
}

TEST_CASE("CHECK FILE NO OVERLAPPING", "[!mayfail]") //TODO contents comparison
{
    auto no_overlapping_result = std::filesystem::path{"spectral_chirp.png"};
    auto no_overlapping_source = std::filesystem::path{"resources"} / no_overlapping_result;
    CHECK(std::filesystem::file_size(no_overlapping_source) == std::filesystem::file_size(no_overlapping_result));
}

TEST_CASE("CHECK FILE OVERLAPPING", "[!mayfail]") //TODO contents comparison
{
    auto overlapping_result = std::filesystem::path{"spectral_chirp_overlaps.png"};
    auto overlapping_source = std::filesystem::path{"resources"} / overlapping_result;
    CHECK(std::filesystem::file_size(overlapping_result) == std::filesystem::file_size(overlapping_result));
}
