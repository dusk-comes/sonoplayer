#include "common.hpp"
#include <sndfile.hh>

class soundfile
{
    public:
        soundfile() = delete;
        soundfile(const char*) noexcept(false);
        ~soundfile() = default;

        int samplerate() const;
        int channels() const;
        std::size_t frames() const;
        std::size_t data(SAMPLE*, std::size_t);

    private:
        SndfileHandle m_file;
};
