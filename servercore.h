#ifndef SERVERCORE_H
#define SERVERCORE_H

#include <mutex>
#include <condition_variable>
#include <atomic>

#include "basecamera.h"
#include "imgprocessor.h"
#include "encoder.h"

class ServerCore
{
public:
    ServerCore();
public:
    void start();
    void stop();
    std::unique_ptr<QImage> get();
    void setCam(int idx);
    void releaseCam();
    void setProc();
    void setEncode();
private:
    std::atomic_bool isRun, haveChildThread;
    std::mutex mtx, buffmtx, processormtx, cammtx;
    std::unique_ptr<QImage> buff;
    std::condition_variable condition;
    BaseCamera cam;
    ImgProcessor processor;
    Encoder encoder;
};

#endif // SERVERCORE_H
