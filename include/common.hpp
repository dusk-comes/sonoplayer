#ifndef COMMON_HPP
#define COMMON_HPP

#include <math.h>
#include <memory>
#include <complex>

using SAMPLE = double;
using SAMPLE_ARRAY = std::shared_ptr<SAMPLE[]>;

using COMPLEX = std::complex<SAMPLE>;
using COMPLEX_ARRAY = std::unique_ptr<COMPLEX[]>;

#endif /* COMMON_HPP */
