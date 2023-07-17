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

model::data::data(my::time::seconds _x, SAMPLE_ARRAY _y, double _freq) noexcept :
    x{_x},
    y(_y),
    freq_resolution{_freq}
{
}

void model::add_data_to_display(SAMPLE_ARRAY spectr_power)
{
    static auto step = samples_to_seconds(m_sp.segments() - m_sp.overlapped());
    m_offset += step;
    static const auto freq_resolution = static_cast<double>(m_sf.samplerate()) / m_sp.segments();
    m_data_to_display.emplace(m_offset, std::move(spectr_power), freq_resolution);
}

void model::calculate()
{
    while(m_sf.load_data(m_buffer))
    {
        m_data_to_play.push(m_buffer);
        m_sp.calculate(m_buffer, std::bind(&model::add_data_to_display, this, std::placeholders::_1));
    }
}

my::time::seconds model::samples_to_seconds(SAMPLE_SIZE samples)
{
    static auto samplerate = m_sf.samplerate();
    auto fraction = static_cast<double>(samples) / samplerate;
    return my::time::seconds(fraction);
}
