#include "calibrationlabel.h"

CalibrationLabel::CalibrationLabel(QWidget *parent):QLabel(parent){
    // Set minimum size for the window
    this->setMinimumSize(QSize(960,616));
}
CalibrationLabel::~CalibrationLabel(){
    // Delete the pointers
    delete this->p1;
    delete this->p2;
}
void CalibrationLabel::startTheCapture(){
    emit startCaptureSignal();
}
void CalibrationLabel::mousePressEvent(QMouseEvent *event){
    if(this->isPaused){
        if(!this->p1 && !this->p2){
            this->p1 = new QPoint(event->x(),event->y());
            emit newPointClicked();
        } else if(!this->p2){
            this->p2 = new QPoint(event->x(),event->y());
            emit newPointClicked();
        }
    }
}
