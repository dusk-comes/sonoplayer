#include "spectrogram.hpp"
#include "common.hpp"
#include "windowing.hpp"
#include <algorithm>
#include <future>
#include <cmath>
#include <limits>
#include <cassert>

spectrogram::spectrogram(const callback &f) :
    m_segment_size{0},
    m_overlapped{0},
    m_fft{nullptr},
    m_data_handler(f)
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

SAMPLE_SIZE spectrogram::overlapped() const
{
    return m_overlapped;
}

void spectrogram::init_data_handler(const callback &handler)
{
    m_data_handler = handler;
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
    windowing::hamming(data);
}

my::time::milliseconds spectrogram::samples_to_time(double samplerate) const
{
    return my::time::milliseconds(sample_resolution() / samplerate);
}

void spectrogram::prepare()
{
    assert(m_segment_size != 0 && "While prepare calculation");

    m_fft = std::make_unique<fft_routine>(m_segment_size);
}

void spectrogram::calculate(const SAMPLE_ARRAY &data)
{
    assert(m_data_handler != nullptr && "While calculate Power");
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

        m_data_handler(spectr_power);
        std::fill(spectr_power.begin(), spectr_power.end(), 0.);
        std::fill(segment.begin(), segment.end(), 0.);
    }
}

SAMPLE_SIZE spectrogram::sample_resolution() const
{
    return segments() - overlapped();
}

double spectrogram::freq_resolution(double samplerate) const
{
    static const auto freq_resolution = static_cast<double>(samplerate) / segments();
    return freq_resolution;
}

my::time::seconds spectrogram::time_resolution(double samplerate) const
{
    return samples_to_time(samplerate);
}

uint spectrogram::bins() const
{
    static const auto bins = static_cast<uint>(std::floor(segments() / 2));
    return bins;
}

uint spectrogram::stripes(SAMPLE_SIZE frames) const
{
    static const auto stripes = (frames - overlapped()) / (segments() - overlapped());
    return static_cast<uint>(stripes);
}
