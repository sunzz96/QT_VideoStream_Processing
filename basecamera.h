#ifndef BASECAMERA_H
#define BASECAMERA_H

#include "opencv2/core.hpp"
#include "opencv2/videoio.hpp"

class BaseCamera
{
public:
    BaseCamera();
    ~BaseCamera();
public:
    void setCamera(int idx);
    void releaseCamera();
    std::unique_ptr<cv::Mat> getFrame();
private:
    cv::VideoCapture cap;
};

#endif // BASECAMERA_H
