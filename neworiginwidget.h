#ifndef NEWORIGINWIDGET_H
#define NEWORIGINWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFuture>
#include <QtConcurrent>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <originlabel.h>

using namespace QtConcurrent;
using namespace cv;

class NewOriginWidget:public QWidget{
Q_OBJECT

public:
    NewOriginWidget(QMainWindow *parent,int originX,int originY,int distance);
    ~NewOriginWidget();
public slots:
    void updateImage(cv::Mat *frame);
public:
    bool isRunning = false;
    int originX = 0;
    int originY = 0;
    int distance = 0;
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
    QLabel *imgLabel=nullptr;
};

#endif // NEWORIGINWIDGET_H
