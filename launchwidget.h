#ifndef LAUNCHWIDGET_H
#define LAUNCHWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <QFuture>
#include <QtConcurrent>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace QtConcurrent;
using namespace cv;

class LaunchWidget:public QWidget{
Q_OBJECT

public:
    LaunchWidget(QMainWindow *parent,int originX,int originY,int distance);
    ~LaunchWidget();
public slots:
    void updateImage(cv::Mat *frame);
public:
    int originX = 0;
    int originY = 0;
    int distance = 0;
private:
    QMainWindow *parent=nullptr;
    QPushButton *newOriginButton=nullptr;
    QPushButton *mainButton=nullptr;
    QPushButton *calButton=nullptr;
    QPushButton *playerButton=nullptr;
    QLabel *imgLabel=nullptr;
};

#endif // LAUNCHWIDGET_H
