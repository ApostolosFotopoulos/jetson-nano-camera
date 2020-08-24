#include "capturewindow.h"

CaptureWindow::CaptureWindow(QWidget *parent):QMainWindow(parent){
    // Title of the window
    this->setWindowTitle("Capture/Record");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Create the widget for the window
    QWidget *widget = new QWidget(this);

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // Set the capture
    Camera c;
    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }
    this->isRunning = true;

    // Create the clickable label for the capture
    this->imgLabel = new CaptureLabel();
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout);
    QObject::connect(this->imgLabel,&CaptureLabel::startCaptureSignal,this,&CaptureWindow::captureImage);
    this->imgLabel->startTheCapture();

    // Set the main layout to window
    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);
}
CaptureWindow::~CaptureWindow(){

}
void CaptureWindow::closeEvent(QCloseEvent *event){
    if(event->spontaneous()){
        this->isRunning=false;
        this->cap->release();
        QCoreApplication::quit();
    }
    event->accept();
}
void CaptureWindow::captureImage(){
    std::cout<<"adadadasdsadassa"<<std::endl;
}
