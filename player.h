#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <playercontrols.h>
#include <toolbar.h>
#include <video.h>
#include <mainwindow.h>

class Player : public QMainWindow
{
    Q_OBJECT

public:
    Player(QWidget *parent = nullptr);
    ~Player();
public slots:
    void backToMenu();
private:
    QSlider *durationSlider=nullptr;
    QMediaPlayer * player=nullptr;
    Toolbar * tools=nullptr;
    PlayerControls * controls=nullptr;
    Video *videoplayer=nullptr;
protected:
    virtual void wheelEvent(QWheelEvent *event);
};
#endif // PLAYER_H
