#pragma once

#include "iobserver.hpp"
#include "task.hpp"

struct iobservable
{
    virtual void add_listener(task, iobserver_ptr) = 0;
};
