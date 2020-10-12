#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class TestWidget:public QWidget{
public:
    TestWidget(QMainWindow *parent);
    ~TestWidget();
private:
    QMainWindow *parent;
};

#endif // TESTWIDGET_H
