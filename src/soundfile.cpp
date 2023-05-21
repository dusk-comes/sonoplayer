#include "soundfile.hpp"
#include <ios>
#include <sstream>
#include <experimental/filesystem>

soundfile::soundfile(const char *filename)
{
    if (!std::experimental::filesystem::exists(filename))
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
    auto count_read_frames = m_file.readf(buffer.data(), count_max_frames);    
    return count_read_frames;
}
