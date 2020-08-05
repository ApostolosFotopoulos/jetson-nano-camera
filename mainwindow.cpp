#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    // Title of the window
    this->setWindowTitle("Multimedia Player");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Create the widget for the window
    QWidget *widget = new QWidget(this);

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // Initialize the capture
    Camera c;
    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }

    // Read JSON to get the calibration coordinates
    this->readJSON();
    this->isRunning = true;

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
    this->imgLabel->startTheCapture();

    //Create the buttons layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout,Qt::AlignBottom);

    // Create the buttons

    //- origin
    this->newOriginButton = new QPushButton("New origin");
    buttonsLayout->addWidget(this->newOriginButton);

    //- main
    this->mainButton = new QPushButton("Capture");
    buttonsLayout->addWidget(this->mainButton);

    //- calibration
    this->calButton = new QPushButton("Calibrate");
    buttonsLayout->addWidget(this->calButton);

    //- player
    this->playerButton = new QPushButton("Player");
    buttonsLayout->addWidget(this->playerButton);

    // Button events
    QObject::connect(this->newOriginButton,&QPushButton::clicked,this,&MainWindow::goToNewOrigin);
    QObject::connect(this->mainButton,&QPushButton::clicked,this,&MainWindow::goToCapture);
    QObject::connect(this->calButton,&QPushButton::clicked,this,&MainWindow::goToCalibration);
    QObject::connect(this->playerButton,&QPushButton::clicked,this,&MainWindow::goToPlayer);

    // Set the main layout to window
    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);
}

MainWindow::~MainWindow(){

    // Terminate the loop for update
    this->isRunning = false;

    // Clean the events
    QObject::disconnect(this->imgLabel,&ImageLabel::startCaptureSignal,this,&MainWindow::captureImage);
    QObject::disconnect(this->newOriginButton,&QPushButton::clicked,this,&MainWindow::goToNewOrigin);
    QObject::disconnect(this->mainButton,&QPushButton::clicked,this,&MainWindow::goToCapture);
    QObject::disconnect(this->calButton,&QPushButton::clicked,this,&MainWindow::goToCalibration);
    QObject::disconnect(this->playerButton,&QPushButton::clicked,this,&MainWindow::goToPlayer);

}

void MainWindow::captureImage(){
    run([=](){
        while(this->isRunning){
            // Capture the frame
            *this->cap >> this->frame;

            // Get height and width
            int width = this->frame.size().width;
            int height = this->frame.size().height;

            // Horizontal line
            line(this->frame,Point(this->originX,this->originY),Point(this->originX+width,this->originY),Scalar(0,0,255),2);
            line(this->frame,Point(this->originX,this->originY),Point(this->originX-width,this->originY),Scalar(0,0,255),2);

            // Vertical line
            line(this->frame,Point(this->originX,this->originY),Point(this->originX,this->originY+height),Scalar(0,0,255),2);
            line(this->frame,Point(this->originX,this->originY),Point(this->originX,this->originY-height),Scalar(0,0,255),2);

            // Show the image
            Mat dest;
            cvtColor(this->frame,dest,cv::COLOR_RGB2BGR);
            QImage image1 = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);
            this->imgLabel->setPixmap(QPixmap::fromImage(image1));
        }
    });
}
void MainWindow::readJSON(){
  cout<<"Reading the JSON..."<<endl;

  // Open the file
  QFile file_obj("./params.json");
  if(!file_obj.open(QIODevice::ReadOnly)){
    cout<<"Failed to open ./params.json";
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

  // Set the parameters
  this->originX = json_map["originX"].toInt();
  this->originY = json_map["originY"].toInt();
  std::cout<<json_string.toLocal8Bit().constData()<<std::endl;
}

void MainWindow::goToNewOrigin(){
    std::cout<<"New origin"<<std::endl;
    this->hide();
    this->isRunning=false;
    this->cap->release();
    NewOriginWindow *w = new NewOriginWindow();
    w->show();
    this->close();
}
void MainWindow::goToCapture(){
    std::cout<<"Capture"<<std::endl;
}
void MainWindow::goToCalibration(){
    std::cout<<"Calibration"<<std::endl;
    this->hide();
    this->isRunning=false;
    this->cap->release();
    CalibrationWindow *w = new CalibrationWindow();
    w->show();
    this->close();
}
void MainWindow::goToPlayer(){
    std::cout<<"Player"<<std::endl;
    this->hide();
    this->isRunning=false;
    this->cap->release();
    Player *w = new Player();
    w->show();
    this->close();
}
void MainWindow::closeEvent(QCloseEvent *event){
    if(event->spontaneous()){
        this->isRunning=false;
        this->cap->release();
        QCoreApplication::quit();
    }
    event->accept();
}

