#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QIcon>
#include <QPushButton>
#include <QComboBox>
#include <QMediaPlayer>
#include <QLabel>
#include <QGroupBox>
#include <rangeslider.h>

class PlayerControls:public QWidget{
Q_OBJECT

public:
    PlayerControls(QMediaPlayer * player);
    ~PlayerControls();
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
    QSlider *durationSlider=nullptr;
    QMediaPlayer *player=nullptr;
    qint64 duration=-1;
    QLabel *durationLabel=nullptr;
    RangeSlider *rangeSlider=nullptr;
    int upperLimit=0;
    int lowerLimit=0;
private:
    qreal playbackRate();
};

#endif // PLAYERCONTROLS_H
