#pragma once

#include <vector>
#include "edgecv/core.hpp"
#include <cstdint>

struct Frame {
    uint8_t* data;
    int      width, height, channels;
};

edgecv::Tensor preprocess_frame(const Frame& f, int target_w, int target_h);