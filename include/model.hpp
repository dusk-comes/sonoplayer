#pragma once

#include "common.hpp"
#include "spectrogram.hpp"
#include "soundfile.hpp"

#include <queue>

class model
{
    public:
        model() = delete;
        model(const std::filesystem::path&, SAMPLE_SIZE);
        ~model() = default;

        void add_data_to_display(SAMPLE_ARRAY);
        void overlapped(SAMPLE_SIZE);
        void calculate();

        my::time::seconds time_resolution() const;
        double freq_resolutions() const;
        uint bins() const;
        uint stripes() const;

        std::vector<SAMPLE_ARRAY> m_data_to_display;

    private:
        my::time::seconds m_offset;
        soundfile m_sf;
        SAMPLE_ARRAY m_buffer;
        spectrogram m_sp;
        //std::queue<SAMPLE_ARRAY> m_data_to_play;

        my::time::seconds samples_to_seconds(SAMPLE_SIZE) const;
};
