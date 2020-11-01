#ifndef ORIGINLABEL_H
#define ORIGINLABEL_H

#include <QObject>
#include <QLabel>
#include <QFile>
#include <iostream>
#include <QTextStream>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMouseEvent>

class OriginLabel:public QLabel{
Q_OBJECT
public:
    OriginLabel(int *originX,int *originY);
    ~OriginLabel();
public:
    int *originX;
    int *originY;
private:
    void mousePressEvent(QMouseEvent *event);
};

#endif // ORIGINLABEL_H
