#ifndef PROCTASK_H
#define PROCTASK_H

#include "opencv2/core.hpp"

class ProcTask
{
public:
    ProcTask() = default;
public:
    virtual void run(cv::Mat &img) = 0;
};

#endif // PROCTASK_H
