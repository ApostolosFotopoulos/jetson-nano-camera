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
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <imagelabel.h>

using namespace QtConcurrent;
using namespace cv;

class MainWindow : public QMainWindow{
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void captureImage();
    void updateImage();
signals:
    void updateImageSignal();
private:
    QPushButton *newOriginButton;
    QPushButton *mainButton;
    QPushButton *calButton;
    QPushButton *playerButton;
    ImageLabel *imgLabel;
    bool isRunning;
};
#endif // MAINWINDOW_H
