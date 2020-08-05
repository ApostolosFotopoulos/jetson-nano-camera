#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent): QLabel(parent){
    // Set minimum size for the window
    this->setMinimumSize(QSize(960,616));
}
ImageLabel::~ImageLabel(){

}
void ImageLabel::startTheCapture(){
    emit startCaptureSignal();
}
