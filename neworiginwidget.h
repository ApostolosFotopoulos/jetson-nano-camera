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

class NewOriginWidget:public QWidget{
Q_OBJECT

public:
    NewOriginWidget(QMainWindow *parent);
    ~NewOriginWidget();
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
};

#endif // NEWORIGINWIDGET_H
