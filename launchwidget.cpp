#include "launchwidget.h"

LaunchWidget::LaunchWidget(QMainWindow *parent):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

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


    // Update the image

    // -------------------------- Create the down label --------------------------//
    QLabel *label = new QLabel("Do you agree with the below origin?");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout,Qt::AlignBottom);

    this->setMinimumSize(QSize(960,616));
    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
LaunchWidget::~LaunchWidget(){
    #ifdef LOG
    std::cout<<"LaunchWidget destroyed..."<<std::endl;
    #endif
}
