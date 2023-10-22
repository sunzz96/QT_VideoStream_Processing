#ifndef LOWLEVELTASKS_H
#define LOWLEVELTASKS_H

#include "proctask.h"

class LowLevelTasks : public ProcTask
{
public:
    virtual void run(cv::Mat &img)  = 0;
};

class GaussianBlur : public LowLevelTasks
{
public:
    virtual void run(cv::Mat &img) override;
};

#endif // LOWLEVELTASKS_H
