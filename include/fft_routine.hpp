#ifndef SPECTR_HPP
#define SPECTR_HPP

#include "common.hpp"
#include <fftw3.h>
#include <complex>
#include <memory>


class fft_routine
{
    private:
        REAL_ARRAY m_input;
        COMPLEX_ARRAY m_output;
        fftw_plan m_plan;

    public:
        fft_routine() = delete;
        explicit fft_routine(const std::size_t);
        ~fft_routine();

        COMPLEX_ARRAY calculate(const SAMPLE_ARRAY&);
        std::size_t series_size() const;
};

#endif /* SPECTR_HPP */
