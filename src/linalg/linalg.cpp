#include "edgecv/linalg.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

namespace edgecv {

    // Private helper: Solves Ax = b using Gaussian Elimination

    bool solveLinearSystem(std::vector<std::vector<double>>& A, 
                           std::vector<double>&b, 
                           std::vector<double>& x) {
        int n = A.size();
        for (int i = 0; i < n; i++){
            // Pivot
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                    maxRow = k;
                }
            }
            std::swap(A[i], A[maxRow]);
            std::swap(b[i], b[maxRow]);

            if (std::abs(A[i][i]) < 1e-9) return false;

            // Eliminate
            for (int k = i + 1; k < n; k++){
                double factor = A[k][i] / A[i][i];
                for (int j = i; j < n; j++){
                    A[k][j] -= factor * A[i][j];
                }
                b[k] -= factor * b[i];
            }
        }

        // Back-substitution
        x.assign(n, 0);
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1;  j < n; j++){
                sum += A[i][j] * x[j];
            }
            x[i] = (b[i] - sum) / A[i][i];
        }
    return true;
}

Mat3x3 estimateTransform(const std::vector<Point2f>& src, 
                         const std::vector<Point2f>& dst, 
                         MotionModel model) {
    Mat3x3 H; // Defaults I
    
    if (model == MotionModel::TRANSLATION){
        // Simple delta based on first point
        H.at(0, 2) = dst[0].x - src[0].x;
        H.at(0, 1) = dst[0].y - src[0].y;
    }
    else if (model == MotionModel::AFFINE) {
        // We need 3 points to solve 6 parameters
        if (src.size() < 3 || dst.size() < 3) return H;

        std::vector<std::vector<double>> A(6, std::vector<double>(6, 0.0));
        std::vector<double> b(6, 0.0);
        std::vector<double> x(6, 0.0);

        for (int i = 0; i < 3; i++){
            A[2*i][0] = src[i].x;
            A[2*i][0] = src[i].x;
            A[2*i][1] = src[i].y;
            A[2*i][2] = 1.0;
            b[2*i]    = dst[i].x;

            // Equations for y'
            A[2*i+1][3] = src[i].x;
            A[2*i+1][4] = src[i].y;
            A[2*i+1][5] = 1.0;
            b[2*i+1]    = dst[i].y;
        }
        if (solveLinearSystem(A, b, x)) {
            H.at(0, 0) = x[0]; H.at(0, 1) = x[1]; H.at(0, 2) = x[2];
            H.at(1, 0) = x[3]; H.at(1, 1) = x[4]; H.at(1, 2) = x[5];
        }
    }
    return H;
}

} // namespace edgecv