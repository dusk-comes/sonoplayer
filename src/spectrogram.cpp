#include "spectrogram.hpp"
#include "window.hpp"
#include "error.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

spectrogram::spectrogram() :
    m_segment_size{0},
    m_overlapping{0},
    m_fft{nullptr}
{}

void spectrogram::segments(const std::size_t size) {m_segment_size = size;}

void spectrogram::overlapping(const std::size_t size) {m_overlapping = (size < m_segment_size) ? size : m_segment_size;}

void spectrogram::normalize(COMPLEX_ARRAY &series_f) const
{
    std::transform(series_f.begin(), series_f.end(),
            series_f.begin(),
            [this](auto value) {return value *= 2. /  m_segment_size;});
}

void spectrogram::magnitude(COMPLEX_ARRAY &series_f, const SAMPLE_ARRAY &output) const
{
    std::transform(series_f.begin(), series_f.end(), output.get(), [](auto value) {
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
    }

    m_fft = std::make_unique<spectr>(m_segment_size);
}

void spectrogram::calculate(const SAMPLE_ARRAY &data, const std::size_t data_size, const std::function<void(SAMPLE_ARRAY, std::size_t)> &callback)
{
    static const SAMPLE_ARRAY segment(new SAMPLE[m_segment_size]);
    const auto step = m_segment_size - m_overlapping;

    for (std::size_t segment_begin = 0, segment_end = segment_begin + m_segment_size;
            segment_begin < data_size;
            segment_begin += step, segment_end = segment_begin + m_segment_size)
    {
        segment_end = (segment_end < data_size) ? segment_end : data_size;
        std::copy(data.get() + segment_begin, data.get() + segment_end, segment.get());

        apply_windowing(segment, m_segment_size);
        auto series_f = m_fft->calculate(segment, m_segment_size);
        normalize(series_f);

        static const SAMPLE_ARRAY spectr_power(new SAMPLE[m_fft->series_size()]);
        magnitude(series_f, spectr_power);

        callback(spectr_power, m_fft->series_size());
        std::fill(spectr_power.get(), spectr_power.get() + m_fft->series_size(), 0.);
        std::fill(segment.get(), segment.get() + m_fft->series_size(), 0.);
    }
}
