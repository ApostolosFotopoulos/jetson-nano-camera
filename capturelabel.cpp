#include "capturelabel.h"


CaptureLabel::CaptureLabel(QWidget * parent):QGraphicsView(parent){
    this->scene = new QGraphicsScene();

    this->setMouseTracking(true);

    this->setScene(scene);

    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);

    this->pixmap = QPixmap(960,616);
    this->pixmapItem = this->scene->addPixmap(pixmap);

    QObject::connect(this,&CaptureLabel::refreshSignal,this,&CaptureLabel::refreshImage);
}
CaptureLabel::~CaptureLabel(){
    QObject::disconnect(this,&CaptureLabel::refreshSignal,this,&CaptureLabel::refreshImage);
}

void CaptureLabel::changeImage(){
    emit refreshSignal();
}
void CaptureLabel::startTheCapture(){
    emit startCaptureSignal();
}

void CaptureLabel::refreshImage(){
    this->pixmapItem->setPixmap(this->pixmap);
    this->update();
}
void CaptureLabel::wheelEvent(QWheelEvent *event){

    // Get the coordinates
    this->mouseX = event->x();
    this->mouseY = event->y();

    // Change the scale factor of the image
    if(event->delta() > 0){
        this->scaleFactor += 0.1;
        scale(1.2,1.2);
    } else if(event->delta() < 0){
        this->scaleFactor -=0.1;
        scale(0.8,0.8);
    }
}
