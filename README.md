# QT视频流处理

## 依赖

QT6.5, OpenCV 3.7

## 框架设计

为了提高可扩展性，采用前后端分离设计，基于C/S模型。

MainWindow 前端实现

ServerCore 后端计算单元，一个图像实时处理实例创建一个计算单元

|- BaseCamera 目前实现本地摄像头帧图像调取

|- ImgProcessor 图像处理模块，管理ProcTask序列

|- Encoder 编码接口，未使用

## BaseCamera

实现了相机的启动与关闭，单帧数据获取。

## ImgProcessor

ImgProcessor 维护ProcTask序列（链表），并对每张图像依次执行链表中的任务

[abstract] ProcTask <- [abstract] LowLevelTask <- 具体方法

策略模式。具体方法重写`void run(cv::Mat &img)`方法，ProcTask与LowLevelTask仅作为接口使用

## Encoder

该部分设计作为remote processing时码流编码扩展模块使用，目前没有接入。

## ServerCore

不断刷新自己的缓冲区，外部获取数据函数与计算函数竞争缓冲区资源

用两个bool变量标识服务器核心运行状态、子线程退出状态，保证每个服务核心只有一个运算子线程。该变量支持原子操作，以减少锁的使用。

