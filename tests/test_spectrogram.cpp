#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <fstream>

#include "common.hpp"
#include "spectrogram.hpp"

struct chirp { 
    public:
        SAMPLE_ARRAY y;
        double freq_start;
        double freq_end;

        chirp(const std::size_t samples, const double step) :
            y(samples),
            freq_start{0},
            freq_end{0},
            coef(2), 
            initialized(false)
        {
            time_range(step);
        }

        SAMPLE_ARRAY get()
        {
            if (!initialized)
            {
                exec();
                initialized = true;
            }
            return y;
        }

    private:
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
            file << time_delta * time_point << " " << freq_resolution * bin << " " << vec[time_point][bin] << std::endl; 
        }
        file << std::endl;
    }
}


TEST_CASE("SPECTROGRAM")
{
    const double step = 0.001;
    const std::size_t block_length = 128;
    const std::size_t bins = block_length / 2;
    const double samplerate = 1 / step;
    const double freq_resolution = samplerate / block_length;

    chirp data(2 / step, step);
    data.freq_start = 50;
    data.freq_end = 250;

    std::vector<std::vector<double>> result;
    
    auto fill_result = [&result](SAMPLE_ARRAY magnitude) {
        result.push_back(magnitude);
    };

    spectrogram sp;
    sp.segments(block_length);
    sp.prepare();

    SECTION("without overlapping")
    {
        const double time_resolution = block_length / samplerate;

        sp.calculate(data.get(), fill_result);
        write_file("spectral_chirp.dat", result, time_resolution, freq_resolution, bins);
    }

    SECTION("overlapping segments")
    {
        const std::size_t overlapping_blocks = 120;
        sp.overlapping(overlapping_blocks);
        const double time_resolution = (block_length - overlapping_blocks) / samplerate;

        sp.calculate(data.get(), fill_result);
        write_file("spectral_chirp_overlaps.dat", result, time_resolution, freq_resolution, bins);
    }
}
