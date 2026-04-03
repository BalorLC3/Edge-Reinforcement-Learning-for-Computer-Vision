#include <opencv2/opencv.hpp>
#include "edgecv/core.hpp"
#include "edgecv/vision.hpp"


edgecv::Tensor preprocess_frame(const Frame& f, int target_w, int target_h) {
    cv::Mat mat(f.height, f.width, CV_8UC3, f.data);
    cv::Mat resized, normalized;
    cv::resize(mat, resized, {target_w, target_h}, 0, 0, cv::INTER_LINEAR);
    resized.convertTo(normalized, CV_32FC3, 1.0 / 255.0);

    //?convert HWC -> CWH?
}