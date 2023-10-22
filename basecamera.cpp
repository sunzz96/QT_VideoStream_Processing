#include "basecamera.h"


BaseCamera::BaseCamera(){};

BaseCamera::~BaseCamera()
{
    cap.release();
}

void BaseCamera::setCamera(int idx)
{
    cap.open(idx);
}

void BaseCamera::releaseCamera()
{
    cap.release();
}

std::unique_ptr<cv::Mat> BaseCamera::getFrame()
{
    if (!cap.isOpened()) return nullptr;

    std::unique_ptr<cv::Mat> cache(new cv::Mat);
    cap >> *cache;
    return std::move(cache);
}
