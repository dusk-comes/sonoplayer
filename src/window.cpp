#include "window.hpp"
#include "common.hpp"
#include <cmath>
#include <functional>
#include <algorithm>

void window::hanning(const SAMPLE_ARRAY &data, const std::size_t size)
{
    auto func = [size, index = 0](SAMPLE &sample) mutable {
        sample *= 0.5 - 0.5 * std::cos(2 * M_PI * index++ / (size - 1));
    };

    std::for_each(data.get(), data.get() + size, func);
}

void window::hamming(const SAMPLE_ARRAY &data, const std::size_t size)
{
    auto func = [size, index = 0](SAMPLE &sample) mutable {
        sample *= 0.54 - 0.46 * std::cos(2 * M_PI * index++ / (size - 1));
    };

    std::for_each(data.get(), data.get() + size, func);
}

void window::blackman(const SAMPLE_ARRAY &data, const std::size_t size)
{
    auto func = [size, index = 0](SAMPLE &sample) mutable {
        sample *= 0.42
            - 0.5 * std::cos(2 * M_PI * index / (size - 1))
            + 0.08 * std::cos(4 * M_PI * index / (size - 1));
        ++index;
    };

    std::for_each(data.get(), data.get() + size, func);
}

void window::flattop(const SAMPLE_ARRAY &data, const std::size_t size)
{
    auto func = [size, index = 0](SAMPLE &sample) mutable {
        sample *= 0.21557895
            - 0.41663158 * std::cos(2 * M_PI * index / (size - 1))
            + 0.277263158 * std::cos(4 * M_PI * index / (size - 1))
            - 0.083578947 * std::cos(6 * M_PI * index / (size - 1))
            + 0.006947368 * std::cos(8 * M_PI * index / (size - 1));
        ++index;
    };

    std::for_each(data.get(), data.get() + size, func);
}
