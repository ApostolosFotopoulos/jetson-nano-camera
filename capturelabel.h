#ifndef CAPTURELABEL_H
#define CAPTURELABEL_H
#define NUM_POINTS 2
#define RANGE_NUM_VALUES 2
#define BOUND_RANGE 3 // R,G,B
#define COLOR_RANGE 20
#define LOWER 0
#define UPPER 1

#include <QLabel>
#include <QObject>
#include <QWheelEvent>
#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QKeyEvent>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class CaptureLabel:public QGraphicsView{
Q_OBJECT
public:
    CaptureLabel(QWidget *parent=nullptr);
    ~CaptureLabel();
    void startTheCapture();
    void wheelEvent(QWheelEvent *event);
    int mouseX=0;
    int mouseY=0;
    int nPointsSet=0;
    int colorRange[NUM_POINTS][RANGE_NUM_VALUES][BOUND_RANGE];
    cv::Mat *frame=nullptr;
    QGraphicsScene * scene=nullptr;
    QGraphicsPixmapItem * pixmapItem=nullptr;
    QPixmap pixmap;
    void changeImage();
public slots:
    void refreshImage();
signals:
    void startCaptureSignal();
    void refreshSignal();
private:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // CAPTURELABEL_H
