#ifndef CALIBRATIONWINDOW_H
#define CALIBRATIONWINDOW_H

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
#include <calibrationlabel.h>
#include <camera.h>
#include <QFuture>
#include <QtConcurrent>
#include <QRunnable>
#include <QPushButton>
#include <mainwindow.h>
#include <QLineEdit>
#include <math.h>

using namespace cv;
using namespace QtConcurrent;

class CalibrationWindow : public QMainWindow{
Q_OBJECT
public:
    CalibrationWindow(QWidget *parent=nullptr);
    ~CalibrationWindow();
public slots:
    void backToMenu();
    void captureImage();
    void calibrate();
    void pause();
    void renderPoint();
private:
    bool isRunning = false;
    bool isUpdated = false;
    cv::VideoCapture *cap=nullptr;
    CalibrationLabel *imgLabel=nullptr;
    Mat frame;
    QPushButton *backButton=nullptr;
    QPushButton *calButton=nullptr;
    QPushButton *pauseButton=nullptr;
    QLineEdit *input=nullptr;
    QLabel *warningLabel=nullptr;
    QWidget *widget=nullptr;
    QVBoxLayout *mainLayout=nullptr;
    QHBoxLayout *buttonsLayout=nullptr;
    QHBoxLayout *warningLayout=nullptr;
    QHBoxLayout *imageLayout=nullptr;
    double distance(double x1,double y1,double x2,double y2);
};

#endif // CALIBRATIONWINDOW_H
