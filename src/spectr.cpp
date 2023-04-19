#include "spectr.hpp"
#include <algorithm>

spectr::error::error(const char *msg) : message{msg} {}

const char *spectr::error::what() const throw() {return message;}

spectr::spectr(const std::size_t size) :
    m_samples_count{size}
{
    m_input = fftw_alloc_real(m_samples_count);
    m_output = fftw_alloc_complex(m_samples_count/2 + 1);
    m_plan = fftw_plan_dft_r2c_1d(m_samples_count, m_input, m_output, FFTW_MEASURE);

    if (m_plan == nullptr)
        throw spectr::error("ERROR: couldn't create fftw_plan");
}

spectr::~spectr()
{
    fftw_destroy_plan(m_plan);
    fftw_free(m_input);
    fftw_free(m_output);
}

std::complex<SAMPLE> *spectr::calc(SAMPLE *data, const std::size_t size)
{
    if (size != m_samples_count)
        throw spectr::error("ERROR: input's data exceed fftw rate");

    std::copy(data, data + size, m_input);
    fftw_execute(m_plan);

    return reinterpret_cast<std::complex<SAMPLE> *>(m_output);
}
