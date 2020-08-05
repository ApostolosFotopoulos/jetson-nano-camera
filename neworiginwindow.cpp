#include "neworiginwindow.h"

NewOriginWindow::NewOriginWindow(QWidget *parent): QMainWindow(parent){

    // Title of the window
    this->setWindowTitle("Choose Origin");

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

    // Read the coordinates from JSON
    this->readJSON();
    this->isRunning= true;

    // Create the clickable label for the origin
    this->imgLabel = new OriginLabel();
    QHBoxLayout *imageLayout = new QHBoxLayout();
    imageLayout->addWidget(this->imgLabel);
    imageLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(imageLayout);
    QObject::connect(this->imgLabel,&OriginLabel::startCaptureSignal,this,&NewOriginWindow::captureImage);
    this->imgLabel->startTheCapture();

    //Create the buttons layout
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(buttonsLayout,Qt::AlignBottom);

    // Create the buttons

    //- origin
    this->backButton = new QPushButton("Back to menu");
    buttonsLayout->addWidget(this->backButton);

    // Button events
    QObject::connect(this->backButton,&QPushButton::clicked,this,&NewOriginWindow::backToMenu);

    // Set the main layout to window
    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);
}
NewOriginWindow::~NewOriginWindow(){

    // Stop the capturing
    this->isRunning = false;

    // Clean the events
    QObject::disconnect(this->backButton,&QPushButton::clicked,this,&NewOriginWindow::backToMenu);
    QObject::disconnect(this->imgLabel,&OriginLabel::startCaptureSignal,this,&NewOriginWindow::captureImage);
}

void NewOriginWindow::backToMenu(){
    std::cout<<"Back to menu"<<std::endl;
    this->hide();
    this->isRunning=false;
    this->cap->release();
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}
void NewOriginWindow::captureImage(){
    run([=](){
        while(this->isRunning){

            if(this->imgLabel->originX!=-1 && this->imgLabel->originY!=-1){
                this->originX = this->imgLabel->originX;
                this->originY = this->imgLabel->originY;
            }
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
        std::cout<<"Out....."<<std::endl;
    });
}
void NewOriginWindow::closeEvent(QCloseEvent *event){
    if(event->spontaneous()){
        this->isRunning=false;
        this->cap->release();
        QCoreApplication::quit();
    }
    event->accept();
}
void NewOriginWindow::readJSON(){
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
