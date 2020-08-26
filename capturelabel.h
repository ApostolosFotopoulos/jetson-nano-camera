#ifndef CAPTURELABEL_H
#define CAPTURELABEL_H

#include <QLabel>
#include <QObject>
#include <QWheelEvent>
#include <iostream>

class CaptureLabel:public QLabel{
Q_OBJECT
public:
    CaptureLabel(QWidget *parent=nullptr);
    ~CaptureLabel();
    void startTheCapture();
    void wheelEvent(QWheelEvent *event);
    int mouseX=0;
    int mouseY=0;
    double scaleFactor=1.0;
signals:
    void startCaptureSignal();
};

#endif // CAPTURELABEL_H
