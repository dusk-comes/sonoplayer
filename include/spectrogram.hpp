#pragma once

#include "common.hpp"
#include "spectr.hpp"

#include <memory>
#include <functional>

class spectrogram
{
    private:
        SAMPLE_SIZE m_segment_size;
        SAMPLE_SIZE m_overlapped;
        std::unique_ptr<spectr> m_fft;

        void normalize(COMPLEX_ARRAY&) const;
        void magnitude(COMPLEX_ARRAY&, SAMPLE_ARRAY&) const;
        void apply_windowing(SAMPLE_ARRAY&) const;

    public:
        spectrogram();
        ~spectrogram() = default;

        void segments(const SAMPLE_SIZE);
        SAMPLE_SIZE segments() const;
        void overlapped(const SAMPLE_SIZE);
        SAMPLE_SIZE overlapped() const;
        void prepare();
        void calculate(const SAMPLE_ARRAY&, const std::function<void(SAMPLE_ARRAY)>&);
};
