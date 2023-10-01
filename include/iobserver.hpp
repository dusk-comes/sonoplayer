#pragma once

#include <memory>

#include "common.hpp"

struct iobserver
{
    virtual void update(SAMPLE_ARRAY) = 0;
};

using iobserver_ptr = std::shared_ptr<iobserver>;
