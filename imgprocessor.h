#ifndef IMGPROCESSOR_H
#define IMGPROCESSOR_H

#include <list>
#include "opencv2/core.hpp"

#include "proctask.h"

class ImgProcessor
{
public:
    ImgProcessor();
public:
    void run(cv::Mat &img);
    void push_back(std::unique_ptr<ProcTask> task);
    void clear();
private:
    std::list<std::unique_ptr<ProcTask>> tasks;
};

#endif // IMGPROCESSOR_H
