#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "common.hpp"
#include <functional>

class window
{
    public:
        static void hanning(SAMPLE_ARRAY&);
        static void hamming(SAMPLE_ARRAY&);
        static void blackman(SAMPLE_ARRAY&);
        static void flattop(SAMPLE_ARRAY&);
        //static output_container bartlett(const std::size_t);
        //static output_container kaiser(const std::size_t);
        //static output_container rectangular(const std::size_t);
};

#endif /* WINDOW_HHP */
