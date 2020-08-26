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
#include <QFuture>
#include <QtConcurrent>
#include <QComboBox>
#include <QPushButton>
#include <random>
#include <unistd.h>
#include <mutex>
#include <QWheelEvent>
#include <mainwindow.h>
#include <QTransform>

using namespace QtConcurrent;
using namespace cv;

class CaptureWindow: public QMainWindow{
Q_OBJECT
public:
    CaptureWindow(QWidget *parent=nullptr);
    ~CaptureWindow();
    void closeEvent(QCloseEvent *event);
public slots:
    void captureImage();
    void startRecord();
    void backToMenu();
private:
    bool isRunning = false;
    cv::VideoCapture *cap=nullptr;
    CaptureLabel *imgLabel=nullptr;
    cv::Mat frame;
    cv::Mat *recordFrame=nullptr;
    double FPS;
    double recordFPS;
    double recordWidth;
    double recordHeight;
    QComboBox *recordOptions=nullptr;
    QPushButton *recordButton=nullptr;
    QPushButton *backButton=nullptr;
    bool isRecording=false;
    string recordFileName;
    string generateFileName();
    void recordImage();
    cv::VideoWriter *videoWriter;
    mutex mutexVid;
};

#endif // CAPTUREWINDOW_H
