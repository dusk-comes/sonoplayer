#include "spectr.hpp"
#include "error.hpp"
#include <algorithm>
#include <memory>

spectr::spectr(const std::size_t size) :
    m_input(size),
    m_output(size/2 + 1)
{
    m_plan = fftw_plan_dft_r2c_1d(m_input.size(),
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

COMPLEX_ARRAY spectr::calculate(const SAMPLE_ARRAY &data, const std::size_t size)
{
    if (size != m_input.size())
        throw error("ERROR: input's data exceed fft rate");

    std::copy(data.get(), data.get() + size, m_input.begin());
    fftw_execute(m_plan);

    return m_output;
}
