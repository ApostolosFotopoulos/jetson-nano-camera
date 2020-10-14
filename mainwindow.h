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

/*
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
*/
//using namespace cv;

using namespace QtConcurrent;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
signals:
    void startCaptureSignal();
public slots:
    void goToNewOrigin();
    void goToCapture();
    void goToCalibration();
    void goToPlayer();
    void backToLaunch();
    void captureImage();
public:
    bool isRunning = false;
private:
    QWidget *widget=nullptr;
    int originX = 0;
    int originY = 0;
    int distance = 0;
    //cv::VideoCapture *cap=nullptr;
private:
    void readJSONProperties();
    void startCapturingEvent();
};

#endif // MAINWINDOW_H
