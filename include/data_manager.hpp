#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <list>
#include <utility>
#include <queue>


#include "common.hpp"
#include "iobservable.hpp"
#include "soundfile.hpp"
#include "spectrogram.hpp"

class iview;

class data_manager : public iobservable
{
    public:
        void add_listener(task, iobserver_ptr) override;

    private:
        std::shared_ptr<spectrogram> m_sg;
        std::shared_ptr<soundfile> m_sf;
        std::shared_ptr<iview> m_win;
        std::queue<SAMPLE_ARRAY> m_spectrograms;
        std::mutex m_grams_mutex;

        std::list<std::pair<task, iobserver_ptr>> m_listeners;
};
