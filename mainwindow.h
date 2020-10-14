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

/*
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
*/
//using namespace cv;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void goToNewOrigin();
    void goToCapture();
    void goToCalibration();
    void goToPlayer();
    void backToLaunch();
private:
    QWidget *widget=nullptr;
    //cv::VideoCapture *cap=nullptr;
};

#endif // MAINWINDOW_H
