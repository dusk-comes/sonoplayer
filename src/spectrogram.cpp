#include "spectrogram.hpp"
#include "window.hpp"
#include <algorithm>
#include <future>
#include <cmath>
#include <limits>
#include <cassert>

spectrogram::spectrogram() :
    m_segment_size{0},
    m_overlapped{0},
    m_fft{nullptr}
{}

void spectrogram::segments(const SAMPLE_SIZE size)
{
    m_segment_size = size;
}

SAMPLE_SIZE spectrogram::segments() const
{
    return m_segment_size;
}

void spectrogram::overlapped(const SAMPLE_SIZE size)
{
    m_overlapped = (size < m_segment_size) ? size : m_segment_size;
}

void spectrogram::normalize(COMPLEX_ARRAY &series_f) const
{
    std::transform(series_f.begin(), series_f.end(),
                   series_f.begin(),
                   [this](auto value) {return value *= 2. /  static_cast<double>(m_segment_size);});
}

void spectrogram::magnitude(COMPLEX_ARRAY &series_f, SAMPLE_ARRAY &output) const
{
    std::transform(series_f.begin(), series_f.end(), output.begin(), [](auto value) {
            auto squared_magnitude = std::norm(value);
            return 10. / std::log(10.) * std::log(squared_magnitude + 1e-6);});
}

void spectrogram::apply_windowing(SAMPLE_ARRAY &data) const
{
    window::hamming(data);
}

void spectrogram::prepare()
{
    assert(m_segment_size != 0 && "While prepare calculation");

    m_fft = std::make_unique<spectr>(m_segment_size);
}

void spectrogram::calculate(const SAMPLE_ARRAY &data, const std::function<void(SAMPLE_ARRAY)> &callback)
{
    static SAMPLE_ARRAY segment(m_segment_size);
    const auto step = m_segment_size - m_overlapped;

    using diff_type = SAMPLE_ARRAY::difference_type;
    assert(data.size() <= std::numeric_limits<diff_type>::max() && "While calculate Power");
    auto data_size = static_cast<diff_type>(data.size());

    for (diff_type segment_begin = 0, segment_end = segment_begin + m_segment_size;
            segment_end <= data_size;
            segment_begin += step, segment_end = segment_begin + m_segment_size)
    {
        std::copy(std::next(data.begin(), segment_begin), std::next(data.begin(), segment_end), segment.begin());

        apply_windowing(segment);
        auto series_f = m_fft->calculate(segment);
        normalize(series_f);

        static SAMPLE_ARRAY spectr_power(m_fft->series_size());
        magnitude(series_f, spectr_power);

        auto sending = std::async(std::launch::async, callback, spectr_power);
        std::fill(spectr_power.begin(), spectr_power.end(), 0.);
        std::fill(segment.begin(), segment.end(), 0.);
    }
}
