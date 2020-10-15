#include "calibrationwidget.h"

CalibrationWidget::CalibrationWidget(QMainWindow*parent):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

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
    this->imgLabel = new QLabel("Image");
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout,Qt::AlignCenter);

    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
CalibrationWidget::~CalibrationWidget(){
    #ifdef LOG
    std::cout<<"CalibrationWidget destroyed...."<<std::endl;
    #endif
}
