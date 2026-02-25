#include <opencv2/opencv.hpp>
#include "edgecv/linalg.hpp"
#include <vector>
#include <iostream>

using namespace std;

void printMatrix(const std::string& label, const edgecv::Mat3x3& m) {
    cout << label << "\n";
    cout << "[" << m.at(0,0) << ", " << m.at(0,1) << ", " << m.at(0,2) << "]\n"
         << "[" << m.at(1,0) << ", " << m.at(1,1) << ", " << m.at(1,2) << "]\n"
         << "[" << m.at(2,0) << ", " << m.at(2,1) << ", " << m.at(2,2) << "]\n\n";
}

int main() {
    vector<edgecv::Point2f> origPts = {
        {0.0, 0.0}, 
        {10.0, 0.0}, 
        {0.0, 10.0}
    };

    // Test 1: TRANSLATION (Shift right 5, down 8)
    vector<edgecv::Point2f> transPts = {
        {5.0, 8.0}, 
        {15.0, 8.0}, 
        {5.0, 18.0}
    };
    
    edgecv::Mat3x3 H_trans = edgecv::estimateTransform(origPts, transPts, edgecv::MotionModel::TRANSLATION);
    printMatrix("Translation Test Result", H_trans);
    /* EXPECTED OUTPUT:
       [1, 0, 5]
       [0, 1, 8]
       [0, 0, 1]
    */

    // Test 2: AFFINE (Scale by 2x, Shift right 10)
    vector<edgecv::Point2f> affinePts = {
        {10.0, 0.0}, 
        {30.0, 0.0}, 
        {10.0, 20.0}
    };

    edgecv::Mat3x3 H_affine = edgecv::estimateTransform(origPts, affinePts, edgecv::MotionModel::AFFINE);
    printMatrix("Affine Test Result", H_affine);
    /* EXPECTED OUTPUT:
       [2, 0, 10]
       [0, 2,  0]
       [0, 0,  1]
    */

    return 0;
}