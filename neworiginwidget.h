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


using namespace QtConcurrent;

class NewOriginWidget:public QWidget{
Q_OBJECT

public:
    NewOriginWidget(QMainWindow *parent);
    ~NewOriginWidget();
public:
    bool isRunning = false;
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
    QLabel *imgLabel=nullptr;
private:
    void captureImage();
};

#endif // NEWORIGINWIDGET_H
