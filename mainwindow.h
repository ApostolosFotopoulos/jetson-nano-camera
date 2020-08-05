#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <iostream>
#include <QTimer>
#include <QFuture>
#include <QtConcurrent>
#include <QRunnable>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <imagelabel.h>
#include <camera.h>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QByteArray>
#include <QJsonObject>
#include <QVariantMap>
#include <neworiginwindow.h>
#include <QCloseEvent>
#include <QCoreApplication>
#include <calibrationwindow.h>

using namespace QtConcurrent;
using namespace cv;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readJSON();
public slots:
    void captureImage();
    void goToNewOrigin();
    void goToCapture();
    void goToCalibration();
    void goToPlayer();
    void closeEvent(QCloseEvent *event);
private:
    QPushButton *newOriginButton=nullptr;
    QPushButton *mainButton=nullptr;
    QPushButton *calButton=nullptr;
    QPushButton *playerButton=nullptr;
    ImageLabel *imgLabel=nullptr;
    bool isRunning;
    cv::VideoCapture *cap=nullptr;
    cv::Mat frame;
    int originX;
    int originY;
};
#endif // MAINWINDOW_H
