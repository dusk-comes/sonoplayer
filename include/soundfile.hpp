#pragma once

#include "common.hpp"
#include <sndfile.hh>

#include <filesystem>

class soundfile
{
    public:
        soundfile() = delete;
        explicit soundfile(const std::filesystem::path&) noexcept(false);
        ~soundfile() = default;

        SAMPLE_SIZE samplerate() const;
        SAMPLE_SIZE channels() const;
        std::size_t frames() const;
        std::size_t load_data(SAMPLE_ARRAY&);

    private:
        SndfileHandle m_file;
};
