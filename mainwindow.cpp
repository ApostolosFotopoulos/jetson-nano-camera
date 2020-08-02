#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){

    this->isRunning = true;

    // Title of the window
    this->setWindowTitle("Multimedia Player");

    // Set the window style
    this->setStyleSheet("font-size:20px;");

    // Create the widget for the window
    QWidget *widget = new QWidget(this);

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // Initialize the capture
    VideoCapture cap(0);

    // ------------------- Contents for the main window ----------------------//

    // Create the label
    QLabel *label = new QLabel("Do you agree with the below origin?");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);

    // Create the image label
    this->imgLabel = new ImageLabel();
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout);
    QObject::connect(this->imgLabel,&ImageLabel::startCaptureSignal,this,&MainWindow::captureImage);
    QObject::connect(this,&MainWindow::updateImageSignal,this,&MainWindow::updateImage);
    this->imgLabel->startTheCapture();

    //Create the buttons layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout,Qt::AlignBottom);

    // Create the buttons

    //- origin
    this->newOriginButton = new QPushButton("New origin");
    buttonsLayout->addWidget(newOriginButton);

    //- main
    this->mainButton = new QPushButton("Capture");
    buttonsLayout->addWidget(mainButton);

    //- calibration
    this->calButton = new QPushButton("Calibrate");
    buttonsLayout->addWidget(calButton);

    //- player
    this->playerButton = new QPushButton("Player");
    buttonsLayout->addWidget(playerButton);

    // Button events

    // Set the main layout to window
    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);

    // Set minimum size for the window
    this->setMinimumSize(QSize(500,500));
}

MainWindow::~MainWindow(){

    // Terminate the loop for update
    this->isRunning = false;

    // Clean the events
    QObject::disconnect(this->imgLabel,&ImageLabel::startCaptureSignal,this,&MainWindow::captureImage);
    QObject::disconnect(this,&MainWindow::updateImageSignal,this,&MainWindow::updateImage);
}

void MainWindow::captureImage(){
    run([=](){
        while(this->isRunning){
           std::cout<<"Capture"<<std::endl;
           emit updateImageSignal();
        }
    });
}
void MainWindow::updateImage(){
    run([=](){
        std::cout<<"Update"<<std::endl;
    });
}

