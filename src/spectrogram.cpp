#include "spectrogram.hpp"
#include "window.hpp"
#include "error.hpp"
#include <vector>
#include <cmath>

spectrogram::spectrogram() :
    m_segment_size{0},
    m_overlapping{0},
    m_overlap_size{0},
    m_ft{nullptr}
{}

void spectrogram::segments(const std::size_t size) {m_segment_size = size;}

void spectrogram::overlapping(const std::size_t size) {m_overlapping = (size > 50) ? 50 : size;}

void spectrogram::apply_windowing(SAMPLE_ARRAY &data, const std::size_t size) const
{
    window::hamming(data, size);
}

void spectrogram::prepare()
{
    if (m_segment_size == 0)
    {
        throw error("ERROR: spectrogram's segments size is 0");
        return;
    }

    m_overlap_size = static_cast<std::size_t>(std::ceil(m_segment_size * m_overlapping / 100));

    m_ft = std::make_unique<spectr>(m_segment_size);
}

void spectrogram::calculate(const SAMPLE_ARRAY &data, const std::size_t data_size)
{
    const SAMPLE_ARRAY segment(new SAMPLE[m_segment_size]);
    static const auto step = m_segment_size - m_overlap_size;

    for (std::size_t segment_begin = 0; segment_begin + m_overlap_size < data_size - segment_begin; segment_begin += step)
    {
        std::copy(segment.get(), segment.get() + m_segment_size, data.get() + segment_begin);
        auto res = m_ft->calculate(segment, m_segment_size);
    }
}

