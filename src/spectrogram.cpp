#include "spectrogram.hpp"
#include "window.hpp"
#include "error.hpp"
#include <algorithm>
#include <cmath>

spectrogram::spectrogram() :
    m_segment_size{0},
    m_overlapping{0},
    m_overlap_size{0},
    m_ft{nullptr}
{}

void spectrogram::segments(const std::size_t size) {m_segment_size = size;}

void spectrogram::overlapping(const std::size_t size) {m_overlapping = (size > 50) ? 50 : size;}

void spectrogram::normalize(const COMPLEX_ARRAY &series_f, const std::size_t size) const
{
    std::for_each(series_f.get(), series_f.get() + size, [this](auto &value) {
                            value /= m_segment_size;});
}

void spectrogram::magnitude(const COMPLEX_ARRAY &series_f, const SAMPLE_ARRAY &output, const std::size_t size) const
{
    std::transform(series_f.get(), series_f.get() + size, output.get(), [](auto value) {
            auto squared_magnitude = std::norm(value);
            return 10. / std::log(10.) * std::log(squared_magnitude + 1e-6);});
}

void spectrogram::apply_windowing(const SAMPLE_ARRAY &data, const std::size_t size) const
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

void spectrogram::calculate(const SAMPLE_ARRAY &data, const std::size_t data_size, const std::function<void(SAMPLE_ARRAY, std::size_t)> &callback)
{
    const SAMPLE_ARRAY segment(new SAMPLE[m_segment_size]);
    static const auto step = m_segment_size - m_overlap_size;

    for (std::size_t segment_begin = 0; segment_begin + m_overlap_size < data_size - segment_begin; segment_begin += step)
    {
        std::copy(data.get() + segment_begin, data.get() + m_segment_size, segment.get());
        apply_windowing(segment, m_segment_size);
        auto series_f = m_ft->calculate(segment, m_segment_size);
        normalize(series_f, m_ft->series_size());
        static const SAMPLE_ARRAY spectr_power(new SAMPLE[m_ft->series_size()]);
        magnitude(series_f, spectr_power, m_ft->series_size());
        callback(spectr_power, m_ft->series_size());
    }
}
