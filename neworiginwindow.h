#ifndef NEWORIGINWINDOW_H
#define NEWORIGINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <camera.h>
#include <QCloseEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <mainwindow.h>
#include <originlabel.h>
#include <QCoreApplication>
#include <camera.h>

using namespace cv;

class NewOriginWindow: public QMainWindow{
Q_OBJECT
public:
    NewOriginWindow(QWidget *parent=nullptr);
    ~NewOriginWindow();
    void closeEvent(QCloseEvent *event);
    void readJSON();
public slots:
    void backToMenu();
    void captureImage();
private:
    cv::VideoCapture *cap=nullptr;
    bool isRunning;
    QPushButton *backButton=nullptr;
    OriginLabel *imgLabel=nullptr;
    int originX;
    int originY;
    Mat frame;
};

#endif // NEWORIGINWINDOW_H
