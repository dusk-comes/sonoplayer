#include "spectr.hpp"
#include "common.hpp"
#include "error.hpp"
#include <algorithm>
#include <memory>
#include <limits>
#include <cassert>

spectr::spectr(const std::size_t size) :
    m_input(size),
    m_output(size/2 + 1)
{
    assert(m_input.size() <= std::numeric_limits<int>::max() && "While creating fftw_plan");

    m_plan = fftw_plan_dft_r2c_1d(static_cast<int>(m_input.size()),
            reinterpret_cast<SAMPLE*>(m_input.data()),
            reinterpret_cast<fftw_complex*>(m_output.data()),
            FFTW_MEASURE);

    if (m_plan == nullptr)
        throw error("ERROR: couldn't create fftw_plan");
}

spectr::~spectr()
{
    fftw_destroy_plan(m_plan);
}

std::size_t spectr::series_size() const
{
    return m_output.size();
}

COMPLEX_ARRAY spectr::calculate(const SAMPLE_ARRAY &data)
{
    if (data.size() != m_input.size())
        throw error("ERROR: input's data exceed fft rate");

    std::copy(data.begin(), data.end(), m_input.begin());
    fftw_execute(m_plan);

    return m_output;
}
