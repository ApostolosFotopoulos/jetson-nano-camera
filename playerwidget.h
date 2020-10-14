#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>

class PlayerWidget:public QWidget{
    Q_OBJECT
public:
    PlayerWidget(QMainWindow *parent);
    ~PlayerWidget();
private:
    QMainWindow *parent=nullptr;
};

#endif // PLAYERWIDGET_H
