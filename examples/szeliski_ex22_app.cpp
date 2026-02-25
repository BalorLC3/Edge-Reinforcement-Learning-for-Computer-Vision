#include <opencv2/opencv.hpp>
#include "edgecv/linalg.hpp"
#include <vector>

using namespace cv;
using namespace std;

// Global state for the mouse interactions
bool isDrawing = false;
int draggedCorner = -1;
Point ptStart;
Rect tempRect;
vector<Point2f> origPts, currentPts;
edgecv::MotionModel currentMode = edgecv::MotionModel::AFFINE;

// Mouse Callback handles the state machine
void onMouse(int event, int x, int y, int flags, void* userdata) {
    if (event == EVENT_LBUTTONDOWN) {
        if (flags & EVENT_FLAG_SHIFTKEY) {
            // Shift + Click: Start drawing a new rectangle
            isDrawing = true;
            ptStart = Point(x, y);
        } else if (!currentPts.empty()) {
            // Normal Click: Check if we are near one of the 4 corners to grab it
            for (int i = 0; i < 4; i++) {
                if (norm(currentPts[i] - Point2f(x, y)) < 15.0) {
                    draggedCorner = i;
                    break;
                }
            }
        }
    } else if (event == EVENT_MOUSEMOVE) {
        if (isDrawing) {
            tempRect = Rect(ptStart, Point(x, y));
        } else if (draggedCorner >= 0) {
            // Update the dragged corner's position
            currentPts[draggedCorner] = Point2f(x, y);
        }
    } else if (event == EVENT_LBUTTONUP) {
        if (isDrawing) {
            isDrawing = false;
            // Save the 4 corners of our newly drawn rectangle
            origPts = {
                Point2f(tempRect.x, tempRect.y),
                Point2f(tempRect.x + tempRect.width, tempRect.y),
                Point2f(tempRect.x + tempRect.width, tempRect.y + tempRect.height),
                Point2f(tempRect.x, tempRect.y + tempRect.height)
            };
            currentPts = origPts;
        }
        draggedCorner = -1; // Let go of the corner
    }
}

int main() {
    namedWindow("EdgeCV Transform Test");
    setMouseCallback("EdgeCV Transform Test", onMouse);
    Mat canvas = Mat::zeros(600, 800, CV_8UC3);

    while (true) {
        Mat display = canvas.clone();
        putText(display, "Shift+Drag to draw a box. Drag RED corners to deform.", Point(15, 30), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 255), 1);

        if (isDrawing) {
            // Draw the green rubber-band box
            rectangle(display, tempRect, Scalar(0, 255, 0), 2);
        } else if (currentPts.size() == 4) {
            
            // BRIDGE TO YOUR LIBRARY 
            vector<edgecv::Point2f> edgeOrig, edgeCurr;
            for (int i = 0; i < 4; ++i) {
                edgeOrig.push_back({origPts[i].x, origPts[i].y});
                edgeCurr.push_back({currentPts[i].x, currentPts[i].y});
            }

            // RUN  
            edgecv::Mat3x3 H_edge = edgecv::estimateTransform(edgeOrig, edgeCurr, currentMode);
            
            // CONVERT BACK AND PROJECT 
            Mat H_cv(3, 3, CV_64F, H_edge.data);
            vector<Point2f> constrainedPts;
            perspectiveTransform(origPts, constrainedPts, H_cv);

            // Force the visible points to obey the math constraint
            // (e.g. Affine forces parallel lines, so dragging a 4th point behaves predictably)
            if (draggedCorner == -1) currentPts = constrainedPts;

            //  DRAW POLYGON 
            for (int i = 0; i < 4; i++) {
                line(display, constrainedPts[i], constrainedPts[(i + 1) % 4], Scalar(255, 100, 0), 2);
                circle(display, constrainedPts[i], 8, Scalar(0, 0, 255), -1);
            }
        }

        imshow("EdgeCV Transform Test", display);
        char key = (char)waitKey(30);
        if (key == 27) break; // Press ESC to close
    }
    return 0;
}