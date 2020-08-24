#ifndef CAPTUREWINDOW_H
#define CAPTUREWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QHBoxLayout>
#include <camera.h>
#include <capturelabel.h>

using namespace cv;
class CaptureWindow: public QMainWindow{
Q_OBJECT
public:
    CaptureWindow(QWidget *parent=nullptr);
    ~CaptureWindow();
    void closeEvent(QCloseEvent *event);
public slots:
    void captureImage();
private:
    bool isRunning = false;
    cv::VideoCapture *cap=nullptr;
    CaptureLabel *imgLabel=nullptr;
};

#endif // CAPTUREWINDOW_H
