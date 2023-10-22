#ifndef ENCODER_H
#define ENCODER_H

#include "opencv2/core.hpp"
#include <QImage>

std::unique_ptr<QImage> cv2q(cv::Mat &src);

class Encoder
{
public:
    Encoder();
private:
};

#endif // ENCODER_H
