#ifndef ORIGINLABEL_H
#define ORIGINLABEL_H

#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFuture>
#include <QtConcurrent>

using namespace QtConcurrent;

class OriginLabel : public QLabel{
Q_OBJECT
public:
    OriginLabel(QWidget *parent=nullptr);
    ~OriginLabel();
    void mousePressEvent(QMouseEvent *event);
    int originX=-1;
    int originY=-1;
    void startTheCapture();
signals:
    void startCaptureSignal();
};

#endif // ORIGINLABEL_H
