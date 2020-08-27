#ifndef CAPTURELABEL_H
#define CAPTURELABEL_H

#include <QLabel>
#include <QObject>
#include <QWheelEvent>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

class CaptureLabel:public QGraphicsView{
Q_OBJECT
public:
    CaptureLabel(QWidget *parent=nullptr);
    ~CaptureLabel();
    void startTheCapture();
    void wheelEvent(QWheelEvent *event);
    int mouseX=0;
    int mouseY=0;
    double scaleFactor=1.0;
    QGraphicsScene * scene=nullptr;
    QGraphicsPixmapItem * pixmapItem=nullptr;
    QPixmap pixmap;
    void changeImage();
public slots:
    void refreshImage();
signals:
    void startCaptureSignal();
    void refreshSignal();
};

#endif // CAPTURELABEL_H
