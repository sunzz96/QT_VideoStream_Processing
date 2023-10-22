#include "servercore.h"

#include <QDebug>
#include <thread>

#include "lowleveltasks.h"

ServerCore::ServerCore()
    :isRun(false), haveChildThread(false)
{

}

void ServerCore::start()
{
    std::unique_lock<std::mutex> lock(mtx);
    if (isRun) {qDebug() << "User tried to rerun a ServerCore."; return;}
    condition.wait(lock, [this](){return !haveChildThread;});
    isRun = true;
    std::thread child([this](){
        haveChildThread = true;
        while (isRun) {
            cammtx.lock();
            auto cacheMat = cam.getFrame();
            cammtx.unlock();

            processormtx.lock();
            processor.run(*cacheMat);
            processormtx.unlock();

            buffmtx.lock();
            buff.reset(cv2q(*cacheMat).release());
            buffmtx.unlock();
        }
        haveChildThread = false;
        condition.notify_one();
    });
    child.detach();
}

void ServerCore::stop()
{
    std::lock_guard<std::mutex> lock(mtx);
    isRun = false;
}

std::unique_ptr<QImage> ServerCore::get()
{
    while (!buff) std::this_thread::sleep_for(std::chrono::milliseconds(8));
    std::lock_guard<std::mutex> lock(buffmtx);
    return std::move(buff);
}

void ServerCore::setCam(int idx)
{
    std::lock_guard<std::mutex> lock(cammtx);
    cam.setCamera(idx);
}

void ServerCore::releaseCam()
{
    std::lock_guard<std::mutex> lock(cammtx);
    cam.releaseCamera();
}

void ServerCore::setProc()
{
    std::lock_guard<std::mutex> lock(cammtx);
    processor.clear();
    std::unique_ptr<GaussianBlur> gb(new GaussianBlur);
    processor.push_back(std::move(gb));
}

void ServerCore::setEncode()
{}
