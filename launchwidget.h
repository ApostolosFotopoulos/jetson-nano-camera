#ifndef LAUNCHWIDGET_H
#define LAUNCHWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class LaunchWidget:public QWidget{
public:
    LaunchWidget(QMainWindow *parent);
    ~LaunchWidget();
private:
    QMainWindow *parent;
};

#endif // LAUNCHWIDGET_H
