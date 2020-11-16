#include "calibrationlabel.h"

CalibrationLabel::CalibrationLabel(){
    this->setMinimumSize(QSize(960,616));
}
CalibrationLabel::~CalibrationLabel(){

}
void CalibrationLabel::mousePressEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();

    std::cout<<x<<std::endl;
    std::cout<<y<<std::endl;
}
