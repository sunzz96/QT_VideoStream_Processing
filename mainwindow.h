#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPermission>
#include <QMediaDevices>
#include <QCameraDevice>
#include <atomic>

#include "servercore.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QCameraPermission cameraPermission;
    QList<QCameraDevice> cameras;
    Ui::MainWindow *ui;
    ServerCore server;
    std::atomic_bool isRun;

public slots:
    void initLocalCam();
    void start();
    void pause();
    void stop();
};
#endif // MAINWINDOW_H
