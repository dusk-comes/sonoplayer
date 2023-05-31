#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP

#include "common.hpp"
#include <sndfile.hh>

#include <filesystem>

class soundfile
{
    public:
        soundfile() = delete;
        explicit soundfile(const std::filesystem::path&) noexcept(false);
        ~soundfile() = default;

        int samplerate() const;
        int channels() const;
        std::size_t frames() const;
        std::size_t data(SAMPLE_ARRAY&);

    private:
        SndfileHandle m_file;
};

#endif /* SOUNDFILE_HPP */
