#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <QPushButton>

class CalibrationWidget:public QWidget{
Q_OBJECT

public:
    CalibrationWidget(QMainWindow *parent);
    ~CalibrationWidget();
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
    QLabel *imgLabel=nullptr;
};

#endif // CALIBRATIONWIDGET_H
