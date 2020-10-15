#ifndef VIDEO_H
#define VIDEO_H

#include <QObject>
#include <QWidget>
#include <QMediaPlayer>
#include <QGraphicsVideoItem>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <playercontrols.h>
#include <QLabel>

class Video:public QWidget{
    Q_OBJECT
public:
    Video(QWidget *parent = nullptr);
    ~Video();
    QMediaPlayer *getPlayer();
private:
    QMediaPlayer *player = nullptr;
    QVideoWidget *videoWidget = nullptr;
};

#endif // VIDEO_H
