#pragma once

#include <memory>

#include "common.hpp"

struct iobserver
{
    virtual void update(SAMPLE_ARRAY) = 0;
};

using iobserver_ptr = std::weak_ptr<iobserver>;
