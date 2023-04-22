#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <fstream>
#include <iterator>
#include <numeric>
#include <vector>
#include <complex>

#include "spectr.hpp"

using complex = std::complex<SAMPLE>;

TEST_CASE("SPECTR OF NATURAL ROW", "[exp]")
{
    std::ifstream numpy_out{"resources/ft_natural_row.txt"};
    std::vector<complex> expected{std::istream_iterator<complex>(numpy_out), std::istream_iterator<complex>()};
    const auto row_size = (expected.size() - 1) * 2;

    SAMPLE_ARRAY data(new SAMPLE[row_size]);
    std::iota(data.get(), data.get() + row_size, 0);

    spectr sp(row_size);
    auto result = sp.calculate(data, row_size);

    for (std::size_t i = 0; i < expected.size(); ++i)
    {
        REQUIRE(expected[i].real() == Catch::Approx(result[i].real()).margin(0.000001));
        REQUIRE(expected[i].imag() == Catch::Approx(result[i].imag()).margin(0.000001));
    }
}
