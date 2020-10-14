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


class LaunchWidget:public QWidget{
Q_OBJECT

public:
    LaunchWidget(QMainWindow *parent);
    ~LaunchWidget();
private:
    QMainWindow *parent=nullptr;
    QPushButton *newOriginButton=nullptr;
    QPushButton *mainButton=nullptr;
    QPushButton *calButton=nullptr;
    QPushButton *playerButton=nullptr;
    QLabel *imgLabel=nullptr;
};

#endif // LAUNCHWIDGET_H
