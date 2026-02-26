#include <iostream>
#include <chrono>
#include <vector>
#include <opencv2/opencv.hpp>
#include "edgecv/linalg.hpp"

using namespace std;
using namespace cv;

int main() {
    const int iterations = 100000; // Run 100k times for a good average
    
    // Define test points
    vector<Point2f> cvSrc = {{0,0}, {100,0}, {0,100}};
    vector<Point2f> cvDst = {{10,10}, {120,5}, {15,110}};
    
    // Convert to library format
    vector<edgecv::Point2f> edgeSrc = {{0,0}, {100,0}, {0,100}};
    vector<edgecv::Point2f> edgeDst = {{10,10}, {120,5}, {15,110}};

    cout << "STARTING benchmark with " << iterations << " iterations...\n" << endl;

    // Benchmark OpenCV 
    auto startCV = chrono::high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i) {
        Mat H = getAffineTransform(cvSrc, cvDst);
    }
    auto endCV = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> diffCV = endCV - startCV;

    // --- Benchmark EdgeCV (Your Library) ---
    auto startEdge = chrono::high_resolution_clock::now();
    for(int i = 0; i < iterations; ++i) {
        edgecv::Mat3x3 H = edgecv::estimateTransform(edgeSrc, edgeDst, edgecv::MotionModel::AFFINE);
    }
    auto endEdge = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> diffEdge = endEdge - startEdge;

    // At this moment is expected that EdgeCV is slower as is still in development
    cout << "RESULTS" << endl;
    cout << "OpenCV getAffineTransform: " << diffCV.count() << " ms total (" 
         << (diffCV.count() * 1000 / iterations) << " us per call)" << endl;
    
    cout << "EdgeCV estimateTransform: " << diffEdge.count() << " ms total (" 
         << (diffEdge.count() * 1000 / iterations) << " us per call)" << endl;

    double ratio = diffEdge.count() / diffCV.count();

    if (ratio > 1.0){
        cout << "\nEdgeCV is " << ratio << "x slower than OpenCV." << endl;
    } else {
        cout << "\nEdgeCV is " << ratio << "x faster than OpenCV." << endl;
    }

    return 0;
}