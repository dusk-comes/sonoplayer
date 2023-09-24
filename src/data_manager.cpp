#include "data_manager.hpp"

void data_manager::add_listener(task t, iobserver_ptr l)
{
    m_listeners.emplace_back(t, l);
}
