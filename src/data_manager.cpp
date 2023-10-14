#include "data_manager.hpp"
#include "spectrogram.hpp"

data_manager::data_manager(const std::filesystem::path& filename) :
    m_sf(filename),
    m_pause(false),
    m_stope(true)
{
    m_thread_for_grams = std::thread(&data_manager::worker_for_grams, this);
}

data_manager::~data_manager()
{
    m_thread_for_grams.detach();
}

void data_manager::add_listener(task t, iobserver_ptr l)
{
    m_listeners.emplace_back(t, l);
}

void data_manager::setup_core(std::shared_ptr<spectrogram> &sg)
{
    m_sg = sg;
    using namespace std::placeholders;
    m_sg->init_data_handler(std::bind(&data_manager::receive_grams, this, _1));
}

void data_manager::play(const SAMPLE_SIZE buffer_size)
{
    SAMPLE_ARRAY buffer(buffer_size);
    while(m_sf.load_data(buffer))
    {
        m_sg->calculate(buffer);
    }
}

void data_manager::receive_grams(SAMPLE_ARRAY &grams)
{
    {
        std::lock_guard lk(m_grams_mutex);
        m_grams.emplace(grams);
    }
    m_condition.notify_all();
}

void data_manager::worker_for_grams()
{
    while(!m_stope)
    {
        std::unique_lock lk(m_grams_mutex);
        m_condition.wait(lk, [this]() {return !m_pause && !m_grams.empty();});

        if (m_stope) break;

        auto stripe = m_grams.front();
        m_grams.pop();
        lk.unlock();

        for (const auto &ctx : m_listeners)
        {
            if (ctx.first == task::display)
                ctx.second->update(stripe);
        }
    }
}

double data_manager::freq_domain() const
{
    return m_sg->bins() * m_sg->freq_resolution(m_sf.samplerate());
}

double data_manager::time_domain() const
{
    return m_sg->stripes(m_sf.frames()) * m_sg->time_resolution(m_sf.samplerate()).count();
}
