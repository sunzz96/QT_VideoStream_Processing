#include "lowleveltasks.h"

#include "opencv2/imgproc.hpp"

void GaussianBlur::run(cv::Mat &img)
{
    cv::GaussianBlur(img, img, cv::Size(51, 51), 0, 0);
}
