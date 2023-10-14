#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <list>
#include <utility>
#include <queue>

#include "common.hpp"
#include "iobservable.hpp"
#include "soundfile.hpp"
#include "spectrogram.hpp"

class data_manager : public iobservable
{
    public:
        data_manager() = delete;
        data_manager(const std::filesystem::path&);
        ~data_manager();
        void add_listener(task, iobserver_ptr) override;
        void setup_core(std::shared_ptr<spectrogram>&);
        void play(const SAMPLE_SIZE);

        double freq_domain() const;
        double time_domain() const;
        uint bins() const;
        uint stripes() const;

    private:
        soundfile m_sf;
        std::shared_ptr<spectrogram> m_sg;

        std::mutex m_grams_mutex;
        std::condition_variable m_condition;
        std::atomic_bool m_pause = false;
        std::atomic_bool m_stope = true;

        std::queue<SAMPLE_ARRAY> m_grams;
        std::list<std::pair<task, iobserver_ptr>> m_listeners;

        void worker_for_grams();
        std::thread m_thread_for_grams;

        void receive_grams(SAMPLE_ARRAY&);
};
