#include "encoder.h"

#include <iostream>

Encoder::Encoder()
{

}

std::unique_ptr<QImage> cv2q(cv::Mat &src)
{
    std::unique_ptr<QImage> image(new QImage);
    switch(src.type())
    {
    case CV_8UC1:
        // QImage构造：数据，宽度，高度，每行多少字节，存储结构
        *image = std::move(QImage((const unsigned char*)src.data, src.cols, src.rows, src.step, QImage::Format_Grayscale8));
        break;
    case CV_8UC3:
        *image = std::move(QImage((const unsigned char*)src.data, src.cols, src.rows, src.step, QImage::Format_RGB888));
        *image = image->rgbSwapped(); // BRG转为RGB
        // Qt5.14增加了Format_BGR888
        // image = QImage((const unsigned char*)mat.data, mat.cols, mat.rows, mat.cols * 3, QImage::Format_BGR888);
        break;
    case CV_8UC4:
        *image = std::move(QImage((const unsigned char*)src.data, src.cols, src.rows, src.step, QImage::Format_ARGB32));
        break;
    case CV_16UC4:
        *image = std::move(QImage((const unsigned char*)src.data, src.cols, src.rows, src.step, QImage::Format_RGBA64));
        *image = image->rgbSwapped(); // BRG转为RGB
        break;
    }
    return std::move(image);
}
