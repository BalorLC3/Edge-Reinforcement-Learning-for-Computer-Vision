#pragma once
#include <vector>
#include <algorithm>  

namespace edgecv {


struct Point2f {
    float x = 0.0f, y = 0.0f;
};

struct Mat3x3 {
    float data[9] = {1,0,0, 0,1,0, 0,0,1};  // float, not double
    float&       at(int r, int c)       { return data[r*3+c]; }
    const float& at(int r, int c) const { return data[r*3+c]; }

    // Apply to a 2D point (homogeneous divide)
    Point2f apply(Point2f p) const {
        float w = data[6]*p.x + data[7]*p.y + data[8];
        return { (data[0]*p.x + data[1]*p.y + data[2]) / w,
                 (data[3]*p.x + data[4]*p.y + data[5]) / w };
    }
};

enum class MotionModel { TRANSLATION, AFFINE, HOMOGRAPHY }; 

struct Tensor {
    float*  data     = nullptr;
    int     ndim     = 0;
    int     shape[8]   = {};
    int     strides[8] = {};
    size_t  numel    = 0;
    bool    owns     = false;

    template<typename... Idx>
    float& at(Idx... indices) {
        int idx_arr[] = { static_cast<int>(indices)... };
        size_t flat = 0;
        for (int i = 0; i < ndim; ++i) flat += idx_arr[i] * strides[i];
        return data[flat];
    }

    Tensor slice(int i) const {
        Tensor t;
        t.data  = data + i * strides[0];
        t.ndim  = ndim - 1;
        t.numel = numel / shape[0];
        t.owns  = false;
        std::copy(shape   + 1, shape   + ndim, t.shape);
        std::copy(strides + 1, strides + ndim, t.strides);
        return t;
    }
};
// this is the simplest pool, allocate by bumping a pointer
class Arena {
public:
    explicit Arena(size_t capacity)
        : buf_(static_cast<std::byte*>(
            std::aligned_alloc(64, capacity))), // 64-byte alligned
          cap_(capacity), offset_(0) {
        if (!buf_) throw std::bad_alloc{};
    }
    ~Arena() {std::free(buf_); }

    Arena(const Arena)
};
    ///....

} 