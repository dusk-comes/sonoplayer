#ifndef COMMON_HPP
#define COMMON_HPP

#include <math.h>
#include <memory>
#include <vector>
#include <complex>

#include "alloc.hpp"

using SAMPLE = double;
using SAMPLE_ARRAY = std::shared_ptr<SAMPLE[]>;

using COMPLEX = std::complex<SAMPLE>;
using COMPLEX_ARRAY = std::vector<COMPLEX, fft::alloc_complex<SAMPLE>>;
using REAL_ARRAY = std::vector<SAMPLE, fft::alloc_real<SAMPLE>>;

#endif /* COMMON_HPP */
