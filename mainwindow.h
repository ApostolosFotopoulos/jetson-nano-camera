#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <launchwidget.h>
#include <camera.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
public slots:
    void changeWindow();
private:
    cv::VideoCapture *cap=nullptr;
};

#endif // MAINWINDOW_H
