#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP

#include "common.hpp"
#include <sndfile.hh>

class soundfile
{
    public:
        soundfile() = delete;
        explicit soundfile(const char*) noexcept(false);
        ~soundfile() = default;

        int samplerate() const;
        int channels() const;
        std::size_t frames() const;
        std::size_t data(SAMPLE_ARRAY&);

    private:
        SndfileHandle m_file;
};

#endif /* SOUNDFILE_HPP */
