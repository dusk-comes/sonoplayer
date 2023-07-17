#pragma once

#include <math.h>
#include <vector>
#include <chrono>
#include <complex>

#include "alloc.hpp"

using SAMPLE = double;
using SAMPLE_SIZE = unsigned int;
using SAMPLE_ARRAY = std::vector<SAMPLE>;

using COMPLEX = std::complex<SAMPLE>;
using COMPLEX_ARRAY = std::vector<COMPLEX, fft::alloc_complex<COMPLEX>>;
using REAL_ARRAY = std::vector<SAMPLE, fft::alloc_real<SAMPLE>>;

namespace my::time
{
    using seconds = std::chrono::duration<float>;
    using milliseconds = std::chrono::duration<float, std::milli>;
}
