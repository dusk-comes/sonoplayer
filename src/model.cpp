#include "model.hpp"
#include "common.hpp"

#include <functional>
#include <cassert>
#include <cmath>

model::model(const std::filesystem::path &file, SAMPLE_SIZE size) :
    m_offset(0),
    m_sf(file),
    m_buffer(size, 0)
{
    auto power_size = std::log2(size);
    assert(std::ceil(power_size) == std::floor(power_size) && "Buffer size should be a power of two");

    auto segment_parts = 4u;
    auto segments = m_buffer.size() / segment_parts;
    m_sp.segments(segments);

    auto coefficient = 50. / 100.;
    auto overlapped = static_cast<unsigned int>(static_cast<double>(segments) * coefficient);
    m_sp.overlapped(overlapped);

    m_sp.prepare();
}

void model::add_data_to_display(SAMPLE_ARRAY spectr_power)
{
    m_offset += time_resolution();
    m_data_to_display.emplace(std::move(spectr_power));
}

void model::calculate()
{
    while(m_sf.load_data(m_buffer))
    {
        //m_data_to_play.push(m_buffer);
        m_sp.calculate(m_buffer, std::bind(&model::add_data_to_display, this, std::placeholders::_1));
    }
}

my::time::seconds model::samples_to_seconds(SAMPLE_SIZE samples) const
{
    static auto samplerate = m_sf.samplerate();
    auto fraction = static_cast<double>(samples) / samplerate;
    return my::time::seconds(fraction);
}

my::time::seconds model::time_resolution() const
{
    static auto time_resolution = samples_to_seconds(m_sp.segments() - m_sp.overlapped());
    return time_resolution;
}

double model::freq_resolutions() const
{
    static const auto freq_resolution = static_cast<double>(m_sf.samplerate()) / m_sp.segments();
    return freq_resolution;
}

uint model::bins() const
{
    static const auto bins = static_cast<uint>(std::floor(m_sp.segments() / 2));
    return bins;
}

uint model::stripes() const
{
    static const auto stripes = (m_sf.frames() - m_sp.overlapped()) / (m_sp.segments() - m_sp.overlapped());
    return stripes;
}
