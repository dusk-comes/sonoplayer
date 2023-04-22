#include "spectr.hpp"
#include "error.hpp"
#include <algorithm>
#include <memory>

spectr::spectr(const std::size_t size) :
    m_input_size{size},
    m_output_size{size/2 + 1}
{
    m_input = fftw_alloc_real(m_input_size);
    m_output = fftw_alloc_complex(m_output_size);
    m_plan = fftw_plan_dft_r2c_1d(m_input_size, m_input, m_output, FFTW_MEASURE);

    if (m_plan == nullptr)
        throw error("ERROR: couldn't create fftw_plan");
}

spectr::~spectr()
{
    fftw_destroy_plan(m_plan);
    fftw_free(m_input);
    fftw_free(m_output);
}

auto spectr::calculate(const SAMPLE_ARRAY &data, const std::size_t size) -> COMPLEX_ARRAY
{
    if (size != m_input_size)
        throw error("ERROR: input's data exceed fft rate");

    std::copy(data.get(), data.get() + size, m_input);
    fftw_execute(m_plan);

    COMPLEX_ARRAY result(new COMPLEX[m_output_size]);
    std::copy(reinterpret_cast<COMPLEX *>(m_output),
            reinterpret_cast<COMPLEX *>(m_output) + m_output_size,
            result.get()); 

    return result;
}
