#include "spectr.hpp"

spectr::spectr(const std::size_t segments)
{
    input = fftw_alloc_real(segments);
    output = fftw_alloc_complex(segments/2 + 1);
    plan = fftw_plan_dft_r2c_1d(segments, input, output, FFTW_MEASURE);
}

spectr::~spectr()
{
    fftw_destroy_plan(plan);
    fftw_free(input);
    fftw_free(output);
}
