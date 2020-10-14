#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>

class CaptureWidget:public QWidget{
public:
    CaptureWidget(QMainWindow *parent);
    ~CaptureWidget();
private:
    QMainWindow *parent=nullptr;
};

#endif // CAPTUREWIDGET_H
