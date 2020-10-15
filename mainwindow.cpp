#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow(){

    // Title of the window
    this->setWindowTitle("Multimedia Player");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Initialize the capture
    //Camera c;

    /*

    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }
    std::cout<<"[INFO] Starting the camera...."<<std::endl;

    #endif

    */

    // Create the widget for the window
    this->widget = new LaunchWidget(this);

    // Read the json properties
    this->readJSONProperties();

    this->setMinimumSize(QSize(960,616));

    // Set the main layout to window
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow(){
    #ifdef LOG
    std::cout<<"MainWindow destroyed..."<<std::endl;
    #endif
}
void MainWindow::goToCapture(){

    #ifdef LOG
    std::cout<<"Redirect to capture...."<<std::endl;
    #endif

    // Hide the window
    this->hide();
    this->setWindowTitle("Capture/Record");

    // Create the new widget and show the window then
    this->widget = new CaptureWidget(this);
    this->setCentralWidget(this->widget);
    this->show();

}
void MainWindow::goToCalibration(){

    #ifdef LOG
    std::cout<<"Redirect to Calibration...."<<std::endl;
    #endif

    // Hide the window
    this->hide();
    this->setWindowTitle("Calibration Setup");

    // Create the new widget and show the window then
    this->widget = new CalibrationWidget(this);
    this->setCentralWidget(this->widget);
    this->show();
}
void MainWindow::goToNewOrigin(){

    #ifdef LOG
    std::cout<<"Redirect to New origin...."<<std::endl;
    #endif

    // Hide the window
    this->hide();
    this->setWindowTitle("Choose Origin");

    // Create the new widget and show the window then
    this->widget = new NewOriginWidget(this);
    this->setCentralWidget(this->widget);
    this->show();
}
void MainWindow::goToPlayer(){

    #ifdef LOG
    std::cout<<"Redirect to Player...."<<std::endl;
    #endif

    // Hide the window
    this->hide();
    this->setWindowTitle("Video Player");

    // Create the new widget and show the window then
    this->widget = new PlayerWidget(this);
    this->setCentralWidget(this->widget);
    this->show();
}

void MainWindow::backToLaunch(){
    #ifdef LOG
    std::cout<<"Redirect to Launch...."<<std::endl;
    #endif

    // Hide the window
    this->hide();
    this->setWindowTitle("Multimedia Player");

    // Create the new widget and show the window then
    this->widget = new LaunchWidget(this);
    this->setCentralWidget(this->widget);

    // Read the json properties
    this->readJSONProperties();
    this->show();
}

void MainWindow::readJSONProperties(){
    #ifdef LOG
    std::cout<<"Reading the JSON...."<<std::endl;
    #endif

    // Try to open the file if exist then continue to reading it
    QFile file_obj(":/config/params.json");
    if(!file_obj.open(QIODevice::ReadOnly)){
        std::cout<<"[ERROR] Failed to open params.json"<<std::endl;
        exit(1);
    }

    // Read the content
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();

    // Pass the content from json format to qvariant
    QByteArray json_bytes = json_string.toLocal8Bit();
    auto json_doc=QJsonDocument::fromJson(json_bytes);
    QJsonObject json_obj=json_doc.object();
    QVariantMap json_map = json_obj.toVariantMap();

    // Setup the parameters
    this->originX = json_map["originX"].toInt();
    this->originY = json_map["originY"].toInt();
    this->distance = json_map["distance"].toInt();

    #ifdef LOG
    std::cout<<json_string.toLocal8Bit().constData()<<std::endl;
    #endif
}
