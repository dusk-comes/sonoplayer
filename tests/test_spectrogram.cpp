#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <cmath>
#include <iostream>
#include <fstream>

#include "spectrogram.hpp"

TEST_CASE("SPECTROGRAM", "[exp]")
{
    const double step = 0.001;
    const std::size_t block_length = 128;
    const std::size_t bins = block_length / 2;
    const double samplerate = 1 / step;
    const double freq_resolution = samplerate / block_length;

    spectrogram sp;
    sp.segments(block_length);
    sp.prepare();

    SECTION("no overlapping segments")
    {
        const std::size_t overlapping_blocks = 120;
        sp.overlapping(120);
        const double measurement_duration = (block_length - overlapping_blocks) / samplerate;

        std::vector<double> t(2 / step);
        std::for_each(t.begin(), t.end(), [point=0., step](auto &value) mutable {
                value = point;
                point += step;});

        const int freq_start = 50;
        const int freq_end = 250;
        const int t1 = 2;
        
        auto chirp = [t1, freq_start, freq_end](auto value){
            return std::cos(2 * M_PI * value *
                                (freq_start + (freq_end - freq_start) * std::pow(value, 2) /
                                    (3 * std::pow(t1, 2))
                                )
                    );};

        SAMPLE_ARRAY samples(new SAMPLE[t.size()]);
        std::transform(t.begin(), t.end(), samples.get(), chirp);

        std::vector<std::vector<double>> result;
        
        auto callback = [&result](SAMPLE_ARRAY magnitude, std::size_t size) {
            std::vector<double> tmp;
            std::copy(magnitude.get(), magnitude.get() + size, std::back_inserter(tmp));
            result.push_back(tmp);
        };

        sp.calculate(samples, t.size(), callback);

        std::ofstream file{"spectral_chirp.dat"};
        const double time_delta = measurement_duration / 2; // take a middle's interval to proect a signal's spectrogram on time axis
        for (std::size_t time_point = 1; time_point < result.size(); ++time_point)
        {
            for (std::size_t bin = 1; bin < bins; ++bin)
            {
                file << time_delta * time_point << " " << freq_resolution * bin << " " << result[time_point][bin] << std::endl; 
            }
            file << std::endl;
        }
    }
}
