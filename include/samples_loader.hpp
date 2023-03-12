#include <sndfile.hh>
#include <array>
#include <utility>
#include <functional>

#define BUFFER_SIZE 1024
#define SAMPLE float

class samples_loader
{
    public:
        samples_loader() = delete;
        samples_loader(const char*) noexcept(false);
        ~samples_loader() = default;

        int samplerate() const;
        int channels() const;
        std::size_t frames() const;

        using Block = std::pair<std::array<SAMPLE, BUFFER_SIZE>, std::size_t>;
        Block receive();

    private:
        SndfileHandle m_file;
        std::array<SAMPLE, BUFFER_SIZE> m_buffer;
};
