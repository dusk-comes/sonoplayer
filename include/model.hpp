#pragma once

#include "common.hpp"
#include "spectrogram.hpp"
#include "soundfile.hpp"

#include <queue>
#include <array>

class model
{
    public:
        struct data
        {
            my::time::seconds x;
            SAMPLE_ARRAY y;
            double freq_resolution;

            data() = delete;
            data(my::time::seconds, SAMPLE_ARRAY, double) noexcept;
        };

        model() = delete;
        model(const std::filesystem::path&, SAMPLE_SIZE);
        ~model() = default;

        void add_data_to_display(SAMPLE_ARRAY);
        void overlapped(SAMPLE_SIZE);
        void calculate();

    private:
        my::time::seconds m_offset;
        soundfile m_sf;
        SAMPLE_ARRAY m_buffer;
        my::time::seconds m_step;
        spectrogram m_sp;
        std::queue<data> m_data_to_display;
        std::queue<SAMPLE_ARRAY> m_data_to_play;

        my::time::seconds samples_to_seconds(SAMPLE_SIZE);
};
