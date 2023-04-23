#ifndef SPECTROGRAM_HPP
#define SPECTROGRAM_HPP

#include "common.hpp"
#include "spectr.hpp"
#include <complex>
#include <memory>

class spectrogram
{
    private:
        std::size_t m_segment_size;
        std::size_t m_overlapping;
        std::size_t m_overlap_size;
        std::unique_ptr<spectr> m_ft;

        void apply_windowing(SAMPLE_ARRAY&, const std::size_t) const;

    public:
        spectrogram();
        ~spectrogram() = default;

        void segments(const std::size_t);
        void overlapping(const std::size_t);
        void prepare();
        void calculate(const SAMPLE_ARRAY&, const std::size_t);
};

#endif /* SPECTROGRAM_HPP */
