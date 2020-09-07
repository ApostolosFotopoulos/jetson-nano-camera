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
        scale(1.2,1.2);
    } else if(event->delta() < 0){
        scale(0.8,0.8);
    }
}
void CaptureLabel::mousePressEvent(QMouseEvent *event){
    if(this->nPointsSet < NUM_POINTS && this->frame!=nullptr){

        // Calculate the color range of the point
        cv::Mat hsv;
        cvtColor(*this->frame,hsv,cv::COLOR_BGR2HSV);

        //Retrieve the pixel
        int x = event->x();
        int y = event->y();
        Vec3b pixel = hsv.at<Vec3b>(y,x);

        for(int i=0;i<BOUND_RANGE;i++){
            int c = pixel.val[i];
            //std::cout<<c<<std::endl;
            double ratio = (COLOR_RANGE)/(double)100;

            // Lower range
            this->colorRange[this->nPointsSet][LOWER][i] = int(c - ratio*c);

            // Upper range
            this->colorRange[this->nPointsSet][UPPER][i] = int(c + ratio*c);
        }

        /*
        std::cout<<this->colorRange[this->nPointsSet][LOWER][0]<<std::endl;
        std::cout<<this->colorRange[this->nPointsSet][LOWER][1]<<std::endl;
        std::cout<<this->colorRange[this->nPointsSet][LOWER][2]<<std::endl;
        std::cout<<this->colorRange[this->nPointsSet][UPPER][0]<<std::endl;
        std::cout<<this->colorRange[this->nPointsSet][UPPER][1]<<std::endl;
        std::cout<<this->colorRange[this->nPointsSet][UPPER][2]<<std::endl;

        */
        this->nPointsSet++;
    }
}
void CaptureLabel::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_R){
        std::cout<<"Point reset...."<<std::endl;
        this->nPointsSet = 0;
    }
}
