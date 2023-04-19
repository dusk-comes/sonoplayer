#include "common.hpp"
#include <fftw3.h>

class spectr
{
    public:
        spectr() = delete;
        spectr(const std::size_t);
        ~spectr();

    private:
        SAMPLE *input;
        fftw_complex *output;
        fftw_plan plan;
};
