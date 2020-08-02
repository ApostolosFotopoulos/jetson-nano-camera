#include "imagelabel.h"

ImageLabel::ImageLabel(QWidget *parent): QLabel(parent){

}
ImageLabel::~ImageLabel(){

}
void ImageLabel::startTheCapture(){
    emit startCaptureSignal();
}
