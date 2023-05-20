#ifndef SPECTR_HPP
#define SPECTR_HPP

#include "common.hpp"
#include <fftw3.h>
#include <complex>
#include <memory>


class spectr
{
    private:
        const std::size_t m_input_size;
        const std::size_t m_output_size;
        SAMPLE *m_input;
        COMPLEX_ARRAY m_output;
        fftw_plan m_plan;

    public:
        spectr() = delete;
        spectr(const std::size_t);
        ~spectr();

        COMPLEX_ARRAY calculate(const SAMPLE_ARRAY&, const std::size_t);
        std::size_t series_size() const;
};

#endif /* SPECTR_HPP */
