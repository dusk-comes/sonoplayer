#include "common.hpp"
#include <bits/c++config.h>
#include <fftw3.h>
#include <complex>

class spectr
{
    private:
        const std::size_t m_samples_count;
        SAMPLE *m_input;
        fftw_complex *m_output;
        fftw_plan m_plan;

    public:
        spectr() = delete;
        spectr(const std::size_t);
        ~spectr();

        std::complex<SAMPLE> *calc(SAMPLE*, const std::size_t);

        class error : public std::exception
        {
            private:
                const char *message;

            public:
                error(const char*);
                
                const char *what() const throw();
        };

};
