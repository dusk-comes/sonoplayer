#ifndef SPECTROGRAM_HPP
#define SPECTROGRAM_HPP

#include "common.hpp"
#include "spectr.hpp"
#include <memory>
#include <functional>

class spectrogram
{
    private:
        long m_segment_size;
        long m_overlapping;
        std::unique_ptr<spectr> m_fft;

        void normalize(COMPLEX_ARRAY&) const;
        void magnitude(COMPLEX_ARRAY&, SAMPLE_ARRAY&) const;
        void apply_windowing(SAMPLE_ARRAY&) const;

    public:
        spectrogram();
        ~spectrogram() = default;

        void segments(const long);
        void overlapping(const long);
        void prepare();
        void calculate(const SAMPLE_ARRAY&, const std::function<void(SAMPLE_ARRAY)>&);
};

#endif /* SPECTROGRAM_HPP */
