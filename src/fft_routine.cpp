#include "fft_routine.hpp"
#include "common.hpp"
#include <algorithm>
#include <memory>
#include <limits>
#include <cassert>

fft_routine::fft_routine(const std::size_t size) :
    m_input(size),
    m_output(size/2 + 1)
{
    assert(m_input.size() <= std::numeric_limits<int>::max() && "While creating fftw_plan");

    m_plan = fftw_plan_dft_r2c_1d(static_cast<int>(m_input.size()),
            reinterpret_cast<SAMPLE*>(m_input.data()),
            reinterpret_cast<fftw_complex*>(m_output.data()),
            FFTW_MEASURE);

    assert(m_plan != nullptr && "While creating fftw_plan");
}

fft_routine::~fft_routine()
{
    fftw_destroy_plan(m_plan);
}

std::size_t fft_routine::series_size() const
{
    return m_output.size();
}

COMPLEX_ARRAY fft_routine::calculate(const SAMPLE_ARRAY &data)
{
    assert(data.size() == m_input.size() && "Input data's size equal fft rate");

    std::copy(data.begin(), data.end(), m_input.begin());
    fftw_execute(m_plan);

    return m_output;
}
