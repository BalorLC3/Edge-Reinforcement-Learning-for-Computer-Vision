#pragma once
#include <vector>

namespace edgecv {
    // Lightweight 2D point structure
    struct Point2f {
        float x, y;
        Point2f () : x(0), y(0) {}
        Point2f(float _x, float _y) : x(_x), y(_y) {}
    };
    // Lightweight 3x3 Matrix for 2D transformation
    struct Mat3x3 {
        double data[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1}; // Identity default

        double& at(int row, int col) {return data [row * 3 + col]; }
        const double& at (int row, int col) const { return data[row * 3 + col]; }
    };

    enum class MotionModel { TRANSLATION, AFFINE, PERSPECTIVE };
} // namespace edgecv