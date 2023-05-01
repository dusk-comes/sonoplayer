#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "spectrogram.hpp"

TEST_CASE("SPECTROGRAM", "[exp]")
{
    spectrogram sp;
    sp.segments(8);

    SECTION("no overlapping segments")
    {
    }
}
