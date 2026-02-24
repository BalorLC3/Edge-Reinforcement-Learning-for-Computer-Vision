#pragma once

#include <vector>
#include "edgecv/core.hpp" // Custom lightweight types

namespace edgecv {

    /**
     * @brief Computes the 3x3 transformation matrix between source and destination points.
     * Uses Gaussian Elimination for solving the linear system.
     * * @param src Vector of original points (minimum required depends on model)
     * @param dst Vector of modified/dragged points
     * @param model The geometric constraint to enforce (TRANSLATION, AFFINE, PERSPECTIVE)
     * @return Mat3x3 The computed 3x3 transformation matrix $H$
     */
    Mat3x3 estimateTransform(const std::vector<Point2f>& src, 
                             const std::vector<Point2f>& dst, 
                             MotionModel model);

    /**
     * @brief Applies a 3x3 transformation matrix to a set of 2D points.
     * Handles homogeneous divide for perspective transformations.
     * * @param pts Vector of input points to be transformed
     * @param H The 3x3 transformation matrix
     * @return std::vector<Point2f> The geometrically transformed points
     */
    std::vector<Point2f> applyTransform(const std::vector<Point2f>& pts, 
                                        const Mat3x3& H);

} // namespace edgecv