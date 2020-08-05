#ifndef CALIBRATIONLABEL_H
#define CALIBRATIONLABEL_H

#include <QLabel>
#include <QObject>
#include <QPoint>
#include <QMouseEvent>
#include <iostream>

class CalibrationLabel:public QLabel{
Q_OBJECT
public:
    CalibrationLabel(QWidget *parent=nullptr);
    ~CalibrationLabel();
    void startTheCapture();
    void renderPoints();
    void mousePressEvent(QMouseEvent *event);
    QPoint *p1= nullptr;
    QPoint *p2= nullptr;
    bool isPaused=false;
signals:
    void startCaptureSignal();
    void newPointClicked();

};

#endif // CALIBRATIONLABEL_H
