#ifndef CAPTURELABEL_H
#define CAPTURELABEL_H

#include <QLabel>
#include <QObject>

class CaptureLabel:public QLabel{
Q_OBJECT
public:
    CaptureLabel(QWidget *parent=nullptr);
    ~CaptureLabel();
    void startTheCapture();
signals:
    void startCaptureSignal();
};

#endif // CAPTURELABEL_H
