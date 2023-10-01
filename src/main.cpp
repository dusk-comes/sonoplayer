#include <cmath>
#include <cassert>
#include <memory>
#include <array>

#include "soundfile.hpp"
#include "spectrogram_builder.hpp"

void handler([[maybe_unused]] SAMPLE_ARRAY &ar)
{
}

int main()
{
    SAMPLE_SIZE buffer_size = 4092;
    double overlapping_coef = 0.5;
    spectrogram_builder builder;
    auto sg = builder
        .set_data_length(buffer_size)
        .set_overlapping_coefficient(overlapping_coef)
        .build();

    sg->init_data_handler(handler);
    sg->prepare();

    const std::filesystem::path &filename("");
    std::shared_ptr<soundfile> sf(new soundfile(filename));

    SAMPLE_ARRAY buffer(buffer_size);
    while(sf->load_data(buffer))
    {
        sg->calculate(buffer);
    }
    return 0;
}
