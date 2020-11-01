#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define LOG
#include <QMainWindow>
#include <launchwidget.h>
#include <camera.h>
#include <iostream>
#include <neworiginwidget.h>
#include <calibrationwidget.h>
#include <capturewidget.h>
#include <playerwidget.h>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFuture>
#include <QtConcurrent>
#include <QSizePolicy>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

using namespace QtConcurrent;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
signals:
    void startCaptureSignal();
    void updateImageSignal(cv::Mat *frame);
public slots:
    void goToNewOrigin();
    void goToCapture();
    void goToCalibration();
    void goToPlayer();
    void backToLaunch();
    void captureImage();
public:
    cv::VideoCapture *cap=nullptr;
    cv::Mat *frame=nullptr;
    int originX = 0;
    int originY = 0;
    int distance = 0;
private:
    QWidget *widget=nullptr;
    bool isRunning = false;
private:
    void readJSONProperties();
    void createJSON();
};

#endif // MAINWINDOW_H
