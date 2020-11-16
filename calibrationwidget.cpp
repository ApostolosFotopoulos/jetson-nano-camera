#include "calibrationwidget.h"

CalibrationWidget::CalibrationWidget(QMainWindow*parent):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // -------------------------- Create the main layout --------------------------//
    this->mainLayout = new QVBoxLayout(this);
    this->mainLayout->setAlignment(Qt::AlignVCenter);

    // -------------------------- Create the buttons layout --------------------------//
    this->buttonsLayout = new QHBoxLayout();
    this->buttonsLayout->setAlignment(Qt::AlignTop);
    this->mainLayout->addLayout(this->buttonsLayout,Qt::AlignTop);

    // -------------------------- Create the buttons --------------------------//

    //Back to origin
    this->backButton = new QPushButton("Back");
    this->buttonsLayout->addWidget(this->backButton);
    this->backButton->setStyleSheet("background-color:#686868;");

    // Input for the distance
    this->input = new QLineEdit();
    this->input->setPlaceholderText("Enter the cm for the distance...");
    this->buttonsLayout->addWidget(this->input);

    // Pause button for the points
    this->pauseButton = new QPushButton("Pause");
    this->buttonsLayout->addWidget(this->pauseButton);

    // Calibration button
    this->calButton = new QPushButton("Calibrate");
    this->buttonsLayout->addWidget(this->calButton);

    // Button events
    QObject::connect(this->backButton,SIGNAL(clicked()),this->parent,SLOT(backToLaunch()));

    //Create a clickable label for the origin
    this->imgLabel = new CalibrationLabel();
    this->imageLayout = new QHBoxLayout();
    this->imageLayout->addWidget(this->imgLabel);
    this->imageLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->addLayout(this->imageLayout,Qt::AlignCenter);

    QObject::connect(this->parent,SIGNAL(updateImageSignal(cv::Mat*)),this,SLOT(updateImage(cv::Mat *)));

    this->setLayout(this->mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
CalibrationWidget::~CalibrationWidget(){
    #ifdef LOG
    std::cout<<"CalibrationWidget destroyed...."<<std::endl;
    #endif
}

void CalibrationWidget::updateImage(cv::Mat *frame){

    Mat dest;
    cvtColor(*frame,dest,cv::COLOR_RGB2BGR);
    QImage i = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);
    this->imgLabel->setPixmap(QPixmap::fromImage(i));
}
