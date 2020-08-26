#include "capturelabel.h"


CaptureLabel::CaptureLabel(QWidget * parent):QLabel(parent){
    // Set minimum size for the window
    this->setMinimumSize(QSize(960,616));

    // Activate the mouse tracking
    setMouseTracking(true);

    // Activate scaling
    setScaledContents(true);
}
CaptureLabel::~CaptureLabel(){

}
void CaptureLabel::startTheCapture(){
    emit startCaptureSignal();
}
void CaptureLabel::wheelEvent(QWheelEvent *event){

    // Get the coordinates
    this->mouseX = event->x();
    this->mouseY = event->y();

    // Change the scale factor of the image
    if(event->delta() > 0 && this->scaleFactor < 2.0){
        this->scaleFactor += 0.1;
    } else if(event->delta() < 0 && this->scaleFactor > 1.0){
        this->scaleFactor -=0.1;
    }
}
