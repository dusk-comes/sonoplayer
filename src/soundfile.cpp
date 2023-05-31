#include "soundfile.hpp"
#include <ios>
#include <limits>
#include <cassert>
#include <sstream>
#include <filesystem>

soundfile::soundfile(const char *filename)
{
    if (!std::filesystem::exists(filename))
    {
        std::ostringstream message;
        message << "filename " << filename << " not exists";
        throw std::ios_base::failure(message.str());
    }

    m_file = SndfileHandle(filename);

    if (m_file.error() != SF_ERR_NO_ERROR)
        throw std::ios_base::failure(m_file.strError());
}

int soundfile::samplerate() const
{
    return m_file.samplerate();
}

int soundfile::channels() const
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
