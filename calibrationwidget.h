#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <QPushButton>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <calibrationlabel.h>

using namespace cv;

class CalibrationWidget:public QWidget{
Q_OBJECT

public:
    CalibrationWidget(QMainWindow *parent);
    ~CalibrationWidget();
public slots:
    void updateImage(cv::Mat *frame);
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
    QLabel *imgLabel=nullptr;
    QLineEdit *input=nullptr;
    QPushButton *pauseButton=nullptr;
    QPushButton *calButton=nullptr;
    QVBoxLayout *mainLayout=nullptr;
    QHBoxLayout *buttonsLayout=nullptr;
    QHBoxLayout *imageLayout=nullptr;
};

#endif // CALIBRATIONWIDGET_H
