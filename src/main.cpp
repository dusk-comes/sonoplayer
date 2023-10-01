#include "soundfile.hpp"
#include "spectrogram.hpp"
#include "spectrogram_builder.hpp"
#include "data_manager.hpp"

void handler([[maybe_unused]] SAMPLE_ARRAY &ar)
{
}

int main()
{
    SAMPLE_SIZE buffer_size = 4092;
    double overlapping_coef = 0.5;
    spectrogram_builder builder;
    std::shared_ptr<spectrogram> sg = builder
        .set_data_length(buffer_size)
        .set_overlapping_coefficient(overlapping_coef)
        .build();
    sg->prepare();

    const std::filesystem::path &filename("resources/test.wav");
    data_manager dm(filename);
    dm.setup_core(sg);

    dm.play(buffer_size);

    return 0;
}
