#ifndef SPECTROGRAM_HPP
#define SPECTROGRAM_HPP

#include "common.hpp"
#include "spectr.hpp"
#include <memory>
#include <functional>

class spectrogram
{
    private:
        std::size_t m_segment_size;
        std::size_t m_overlapping;
        std::unique_ptr<spectr> m_fft;

        void normalize(const COMPLEX_ARRAY&, const std::size_t) const;
        void magnitude(const COMPLEX_ARRAY&, const SAMPLE_ARRAY&, const std::size_t) const;
        void apply_windowing(const SAMPLE_ARRAY&, const std::size_t) const;

    public:
        spectrogram();
        ~spectrogram() = default;

        void segments(const std::size_t);
        void overlapping(const std::size_t);
        void prepare();
        void calculate(const SAMPLE_ARRAY&, const std::size_t, const std::function<void(SAMPLE_ARRAY, std::size_t)>&);
};

#endif /* SPECTROGRAM_HPP */
