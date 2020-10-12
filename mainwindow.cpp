#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow(){

    // Title of the window
    this->setWindowTitle("Multimedia Player");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Initialize the capture
    Camera c;
    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }
    std::cout<<"[INFO] Starting the camera...."<<std::endl;

    // Create the widget for the window
    LaunchWidget *widget = new LaunchWidget(this);

    // Set the main layout to window
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow(){

}
void MainWindow::changeWindow(){
    this->hide();
    // Title of the window
    this->setWindowTitle("Second");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    this->show();
}
