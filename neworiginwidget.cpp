#include "neworiginwidget.h"

NewOriginWidget::NewOriginWidget(QMainWindow *parent,int originX,int originY,int distance):QWidget(){
    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;
    this->originX = originX;
    this->originY = originY;
    this->distance = distance;

    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // -------------------------- Create the buttons layout --------------------------//
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(buttonsLayout,Qt::AlignTop);

    // -------------------------- Create the buttons --------------------------//

    //- origin
    this->backButton = new QPushButton("Back");
    buttonsLayout->addWidget(this->backButton);
    this->backButton->setStyleSheet("background-color:#686868;");

    // Button events
    QObject::connect(this->backButton,SIGNAL(clicked()),this->parent,SLOT(backToLaunch()));

    //Create a clickable label for the origin
    this->imgLabel = new OriginLabel(&this->originX,&this->originY);
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout,Qt::AlignCenter);

    QObject::connect(this->parent,SIGNAL(updateImageSignal(cv::Mat*)),this,SLOT(updateImage(cv::Mat *)));

    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
NewOriginWidget::~NewOriginWidget(){
    #ifdef LOG
    std::cout<<"NewOrigin destroyed...."<<std::endl;
    #endif
}
void NewOriginWidget::updateImage(cv::Mat *frame){

    // Get height and width
    int width = (*frame).size().width;
    int height = (*frame).size().height;

    // Horizontal line
    line(*frame,Point(this->originX,this->originY),Point(this->originX+width,this->originY),Scalar(0,0,255),2);
    line(*frame,Point(this->originX,this->originY),Point(this->originX-width,this->originY),Scalar(0,0,255),2);

    // Vertical line
    line(*frame,Point(this->originX,this->originY),Point(this->originX,this->originY+height),Scalar(0,0,255),2);
    line(*frame,Point(this->originX,this->originY),Point(this->originX,this->originY-height),Scalar(0,0,255),2);

    Mat dest;
    cvtColor(*frame,dest,cv::COLOR_RGB2BGR);
    QImage i = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);
    this->imgLabel->setPixmap(QPixmap::fromImage(i));
}
