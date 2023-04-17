#include "window.hpp"
#include "common.hpp"
#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>

auto window::handler(const std::size_t size, const function &func) -> output_container
{
    output_container result(size);
    std::iota(result.begin(), result.end(), 0);
    std::for_each(result.begin(), result.end(), func);
    return result;
}

auto window::hanning(const std::size_t size) -> output_container
{
    auto func = [&size](floating_t &element) {
        element = 0.5  - 0.5 * std::cos(2 * M_PI * element / (size - 1));
    };

    return handler(size, func);
}

auto window::hamming(const std::size_t size) -> output_container
{
    auto func = [&size](floating_t &element) {
        element = 0.54 - 0.46 * std::cos(2 * M_PI * element / (size - 1));
    };

    return handler(size, func);
}

auto window::blackman(const std::size_t size) -> output_container
{
    auto func = [&size](floating_t &element) {
        element = 0.42
            - 0.5 * std::cos(2 * M_PI * element / (size - 1))
            + 0.08 * std::cos(4 * M_PI * element / (size - 1));
    };

    return handler(size, func);
}

auto window::flattop(const std::size_t size) -> output_container
{
    auto func = [&size](floating_t &element) {
        element = 0.21557895
            - 0.41663158 * std::cos(2 * M_PI * element / (size - 1))
            + 0.277263158 * std::cos(4 * M_PI * element / (size - 1))
            - 0.083578947 * std::cos(6 * M_PI * element / (size - 1))
            + 0.006947368 * std::cos(8 * M_PI * element / (size - 1));
    };

    return handler(size, func);
}
