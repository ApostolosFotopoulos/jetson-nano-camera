#include "capturelabel.h"


CaptureLabel::CaptureLabel(QWidget * parent):QLabel(parent){
    // Set minimum size for the window
    this->setMinimumSize(QSize(960,616));
}
CaptureLabel::~CaptureLabel(){

}
void CaptureLabel::startTheCapture(){
    emit startCaptureSignal();
}
