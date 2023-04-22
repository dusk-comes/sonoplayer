#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "common.hpp"
#include <functional>

class window
{
    friend class test_window;

    private:
        using function = std::function<void(SAMPLE&)>;

    public:
        static void hanning(const SAMPLE_ARRAY&, const std::size_t);
        static void hamming(const SAMPLE_ARRAY&, const std::size_t);
        static void blackman(const SAMPLE_ARRAY&, const std::size_t);
        static void flattop(const SAMPLE_ARRAY&, const std::size_t);
        //static output_container bartlett(const std::size_t);
        //static output_container kaiser(const std::size_t);
        //static output_container rectangular(const std::size_t);

};

#endif /* WINDOW_HHP */
