#include "launchwidget.h"

LaunchWidget::LaunchWidget(QMainWindow *parent,int originX,int originY,int distance):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;
    this->originX = originX;
    this->originY = originY;
    this->distance = distance;
    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // -------------------------- Create the buttons --------------------------//
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(buttonsLayout,Qt::AlignTop);

    //- origin
    this->newOriginButton = new QPushButton("New origin");
    buttonsLayout->addWidget(this->newOriginButton);
    this->newOriginButton->setStyleSheet("background-color:#686868;");

    //- main
    this->mainButton = new QPushButton("Capture");
    buttonsLayout->addWidget(this->mainButton);
    this->mainButton->setStyleSheet("background-color:#686868;");

    //- calibration
    this->calButton = new QPushButton("Calibrate");
    buttonsLayout->addWidget(this->calButton);
    this->calButton->setStyleSheet("background-color:#686868;");

    //- player
    this->playerButton = new QPushButton("Player");
    buttonsLayout->addWidget(this->playerButton);
    this->playerButton->setStyleSheet("background-color:#686868;");


    // Button events
    QObject::connect(this->newOriginButton,SIGNAL(clicked()),this->parent,SLOT(goToNewOrigin()));
    QObject::connect(this->mainButton,SIGNAL(clicked()),this->parent,SLOT(goToCapture()));
    QObject::connect(this->calButton,SIGNAL(clicked()),this->parent,SLOT(goToCalibration()));
    QObject::connect(this->playerButton,SIGNAL(clicked()),this->parent,SLOT(goToPlayer()));


    // -------------------------- Create the image label --------------------------//
    this->imgLabel = new QLabel("IMAGE");
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout,Qt::AlignCenter);

    QObject::connect(this->parent,SIGNAL(updateImageSignal(cv::Mat*)),this,SLOT(updateImage(cv::Mat *)));

    // -------------------------- Create the down label --------------------------//
    QLabel *label = new QLabel("Do you agree with the below origin?");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout,Qt::AlignBottom);

    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
LaunchWidget::~LaunchWidget(){
    #ifdef LOG
    std::cout<<"LaunchWidget destroyed..."<<std::endl;
    #endif
}
void LaunchWidget::updateImage(cv::Mat *frame){

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

