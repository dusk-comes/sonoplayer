#include "samples_loader.hpp"
#include <ios>
#include <sstream>
#include <experimental/filesystem>

samples_loader::samples_loader(const char *filename)
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

int samples_loader::samplerate() const
{
    return m_file.samplerate();
}

int samples_loader::channels() const
{
    return m_file.channels();
}

std::size_t samples_loader::frames() const
{
    return m_file.frames();
}

auto samples_loader::receive() -> Block
{
    auto max_count_frame = m_buffer.size() / channels();
    auto read_count_frames = m_file.readf(m_buffer.data(), max_count_frame);    
    return {m_buffer, read_count_frames};
}
