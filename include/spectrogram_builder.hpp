#include <memory>

#include "common.hpp"
#include "spectrogram.hpp"

struct spectrogram_builder
{
    private:
        using builder = spectrogram_builder;
        SAMPLE_SIZE m_segments;
        SAMPLE_SIZE m_overlapped;

    public:
        spectrogram_builder() = default;
        ~spectrogram_builder() = default;

        builder &set_data_length(const std::size_t);
        builder &set_overlapping_coefficient(const double);
        std::unique_ptr<spectrogram> build();
};
