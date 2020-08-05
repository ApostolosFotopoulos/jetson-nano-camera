#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QComboBox>
#include <QMediaPlayer>
#include <iostream>
#include <QMouseEvent>
#include <QTime>
#include <rangeslider.h>

class PlayerControls: public QWidget
{
    Q_OBJECT
public:
    PlayerControls(QWidget *parent = nullptr,QMediaPlayer *player=nullptr);
    ~PlayerControls();
    QSlider *retrieveSlider();
    int retrieveDuration();
signals:
    void changeRate(qreal rate);
private slots:
    void updateRate();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void seek(int seconds);
    void nextClicked();
    void prevClicked();
    void lowerChanged(int val);
    void upperChanged(int val);
private:
    QPushButton *prevButton=nullptr;
    QPushButton *pauseButton=nullptr;
    QPushButton *playButton=nullptr;
    QPushButton *stopButton=nullptr;
    QPushButton *nextButton=nullptr;
    QComboBox *rateBox=nullptr;
    QMediaPlayer *player=nullptr;
    QSlider *durationSlider=nullptr;
    qreal playbackRate();
    void updateDurationInfo(qint64 currentInfo);
    qint64 duration=-1;
    QLabel * durationLabel=nullptr;
    RangeSlider *rangeSlider=nullptr;
    int lowerLimit;
    int upperLimit;
};

#endif // PLAYERCONTROLS_H
