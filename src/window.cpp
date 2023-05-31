#include "window.hpp"
#include "common.hpp"
#include <cmath>
#include <functional>

void window::hanning(SAMPLE_ARRAY &data)
{
    auto func = [size = data.size(), index = 0](SAMPLE &sample) mutable {
        sample *= 0.5 - 0.5 * std::cos(2 * M_PI * index++ / static_cast<double>(size - 1));
    };

    std::for_each(data.begin(), data.end(), func);
}

void window::hamming(SAMPLE_ARRAY &data)
{
    auto func = [size = data.size(), index = 0](SAMPLE &sample) mutable {
        sample *= 0.54 - 0.46 * std::cos(2 * M_PI * index++ / static_cast<double>(size - 1));
    };

    std::for_each(data.begin(), data.end(), func);
}

void window::blackman(SAMPLE_ARRAY &data)
{
    auto func = [size = data.size(), index = 0](SAMPLE &sample) mutable {
        sample *= 0.42
            - 0.5 * std::cos(2 * M_PI * index / static_cast<double>(size - 1))
            + 0.08 * std::cos(4 * M_PI * index / static_cast<double>(size - 1));
        ++index;
    };

    std::for_each(data.begin(), data.end(), func);
}

void window::flattop(SAMPLE_ARRAY &data)
{
    auto func = [size = data.size(), index = 0](SAMPLE &sample) mutable {
        sample *= 0.21557895
            - 0.41663158 * std::cos(2 * M_PI * index / static_cast<double>(size - 1))
            + 0.277263158 * std::cos(4 * M_PI * index / static_cast<double>(size - 1))
            - 0.083578947 * std::cos(6 * M_PI * index / static_cast<double>(size - 1))
            + 0.006947368 * std::cos(8 * M_PI * index / static_cast<double>(size - 1));
        ++index;
    };

    std::for_each(data.begin(), data.end(), func);
}
