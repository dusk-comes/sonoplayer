#include <cmath>
#include <cassert>
#include <memory>

#include "spectrogram.hpp"
#include "spectrogram_builder.hpp"

auto spectrogram_builder::set_data_length(const std::size_t length) -> builder&
{
    assert(std::ceil(std::log2(length)) == std::floor(std::log2(length)) && "fft size should be a power of two");
    auto parts = 4u;
    m_segments = length / parts;
    return *this;
}

auto spectrogram_builder::set_overlapping_coefficient(const double coef) -> builder&
{
    assert(coef >= 0 && coef <= 1 && "overlapping should between 0 and 1");
    m_overlapped = static_cast<uint>(static_cast<double>(m_segments) * coef);
    return *this;
}

std::unique_ptr<spectrogram> spectrogram_builder::build()
{
    auto ptr = std::make_unique<spectrogram>();
    assert(m_segments > 0 && "fft size should be greater than 0");
    ptr->segments(m_segments);
    ptr->overlapped(m_overlapped);
    return ptr;
}
