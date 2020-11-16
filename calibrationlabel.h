#ifndef CALIBRATIONLABEL_H
#define CALIBRATIONLABEL_H

#include <QObject>
#include <QLabel>
#include <QMouseEvent>
#include <iostream>

class CalibrationLabel:public QLabel{
Q_OBJECT
public:
    CalibrationLabel();
    ~CalibrationLabel();
private:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CALIBRATIONLABEL_H
