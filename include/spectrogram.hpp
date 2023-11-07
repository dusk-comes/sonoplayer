#pragma once

#include "common.hpp"
#include "fft_routine.hpp"

#include <memory>
#include <functional>

class spectrogram
{
    private:
        using callback = std::function<void(SAMPLE_ARRAY&)>;

        SAMPLE_SIZE m_segment_size;
        SAMPLE_SIZE m_overlapped;
        const SAMPLE_SIZE m_dc_part{0};
        std::unique_ptr<fft_routine> m_fft;
        callback m_data_handler;

        void normalize(COMPLEX_ARRAY&) const;
        void magnitude(COMPLEX_ARRAY&, SAMPLE_ARRAY&) const;
        void apply_windowing(SAMPLE_ARRAY&) const;
        my::time::milliseconds samples_to_time(double) const;

    public:
        spectrogram() = default;
        spectrogram(const callback&);
        ~spectrogram() = default;

        void segments(const SAMPLE_SIZE);
        SAMPLE_SIZE segments() const;
        void overlapped(const SAMPLE_SIZE);
        SAMPLE_SIZE overlapped() const;
        void init_data_handler(const callback&);
        void prepare();
        void calculate(const SAMPLE_ARRAY&);
        SAMPLE_SIZE sample_resolution() const;
        double freq_resolution(double) const;
        my::time::milliseconds time_resolution(double) const;
        uint bins() const;
        uint stripes(SAMPLE_SIZE) const;
};
