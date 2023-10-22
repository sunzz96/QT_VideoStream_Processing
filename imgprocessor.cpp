#include "imgprocessor.h"

ImgProcessor::ImgProcessor()
{}

void ImgProcessor::run(cv::Mat &img)
{
    for (auto &i : tasks) i->run(img);
}

void ImgProcessor::push_back(std::unique_ptr<ProcTask> task)
{
    tasks.push_back(std::move(task));
}

void ImgProcessor::clear()
{
    tasks.clear();
}
