#ifndef SPECTR_HPP
#define SPECTR_HPP

#include "common.hpp"
#include <fftw3.h>
#include <complex>
#include <memory>


class spectr
{
    private:
        REAL_ARRAY m_input;
        COMPLEX_ARRAY m_output;
        fftw_plan m_plan;

    public:
        spectr() = delete;
        explicit spectr(const std::size_t);
        ~spectr();

        COMPLEX_ARRAY calculate(const SAMPLE_ARRAY&);
        std::size_t series_size() const;
};

#endif /* SPECTR_HPP */
