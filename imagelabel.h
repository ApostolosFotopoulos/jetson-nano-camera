#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QLabel>
#include <QObject>
#include <iostream>

class ImageLabel:public QLabel{
Q_OBJECT

public:
    ImageLabel(QWidget *parent=nullptr);
    ~ImageLabel();
    void startTheCapture();
signals:
    void startCaptureSignal();
};

#endif // IMAGELABEL_H
