#ifndef SPECTR_HPP
#define SPECTR_HPP

#include "common.hpp"
#include <fftw3.h>
#include <complex>
#include <memory>


class spectr
{
    using COMPLEX = std::complex<SAMPLE>;
    using COMPLEX_ARRAY = std::unique_ptr<COMPLEX[]>;

    private:
        const std::size_t m_input_size;
        const std::size_t m_output_size;
        SAMPLE *m_input;
        fftw_complex *m_output;
        fftw_plan m_plan;

    public:
        spectr() = delete;
        spectr(const std::size_t);
        ~spectr();

        COMPLEX_ARRAY calculate(const SAMPLE_ARRAY&, const std::size_t);
};

#endif /* SPECTR_HPP */
