#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#define LOG

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <iostream>
#include <QPushButton>
#include <QFileDialog>
#include <QStandardPaths>
#include <playercontrols.h>
#include <video.h>

class PlayerWidget:public QWidget{
    Q_OBJECT
public:
    PlayerWidget(QMainWindow *parent);
    ~PlayerWidget();
public slots:
    void openFile();
public:
    QMediaPlayer *player = nullptr;
    Video *videoplayer=nullptr;
private:
    QMainWindow *parent=nullptr;
    QPushButton *backButton=nullptr;
    QPushButton *openButton=nullptr;
    QLabel *fileNameLabel=nullptr;
};

#endif // PLAYERWIDGET_H
