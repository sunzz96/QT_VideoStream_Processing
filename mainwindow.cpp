#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QCamera>
#include <QMediaCaptureSession>
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    isRun(false)
{
    ui->setupUi(this);
    initLocalCam();
    connect(ui->actionPlay, &QAction::triggered, this, &MainWindow::start);
    connect(ui->actionStop, &QAction::triggered, this, &MainWindow::stop);
    connect(ui->actionPause, &QAction::triggered, this, &MainWindow::pause);
}

MainWindow::~MainWindow()
{
    if (isRun) stop();
    delete ui;
}

void MainWindow::initLocalCam()
{
#if QT_CONFIG(permissions)
    switch (qApp->checkPermission(cameraPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cameraPermission, this, &MainWindow::initLocalCam);
        return;
    case Qt::PermissionStatus::Denied:
        qWarning("Camera permission is not granted!");
        return;
    case Qt::PermissionStatus::Granted:
        break;
    }
#endif
    cameras = QMediaDevices::videoInputs();
    foreach(QCameraDevice camera , cameras)
    {
        qDebug() << camera.id() << camera.description();
        ui->comboBox->addItem(camera.description());
    }
}

void MainWindow::start()
{
    if (isRun) return;
    server.setCam(ui->comboBox->currentIndex());
    server.setProc();
    server.start();
    std::thread th([this](){
        isRun = true;
        while (isRun) {
            auto img = server.get();
            ui->label->setPixmap((QPixmap::fromImage(*img)).scaled(ui->label->size(),Qt::KeepAspectRatio));
        }
    });
    th.detach();
}

void MainWindow::pause()
{
    isRun = false;
    server.stop();
    server.releaseCam();
}

void MainWindow::stop()
{
    isRun = false;
    server.stop();
    server.releaseCam();
    ui->label->clear();
}
