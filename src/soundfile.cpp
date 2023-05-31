#include "soundfile.hpp"
#include "common.hpp"
#include <filesystem>
#include <ios>
#include <limits>
#include <cassert>
#include <sstream>

soundfile::soundfile(const std::filesystem::path &path)
{
    assert(std::filesystem::exists(path) && "While open file");
    m_file = SndfileHandle(path);

    if (m_file.error() != SF_ERR_NO_ERROR)
        throw std::ios_base::failure(m_file.strError());
}

SAMPLE_SIZE soundfile::samplerate() const
{
    return m_file.samplerate();
}

SAMPLE_SIZE soundfile::channels() const
{
    return m_file.channels();
}

std::size_t soundfile::frames() const
{
    return m_file.frames();
}

std::size_t soundfile::data(SAMPLE_ARRAY &buffer)
{
    auto count_max_frames = buffer.size() / channels();
    assert(count_max_frames <= std::numeric_limits<sf_count_t>::max() && "While read soundfile");
    
    auto count_read_frames = m_file.readf(buffer.data(), static_cast<sf_count_t>(count_max_frames));
    return count_read_frames;
}
