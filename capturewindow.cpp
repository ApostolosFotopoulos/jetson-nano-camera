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
    mainLayout->setAlignment(Qt::AlignCenter);

    // Set the capture
    Camera c;
    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }
    this->isRunning = true;
    this->FPS = this->cap->get(CAP_PROP_FPS);

    // Create the layout for the frame rate and the button for record
    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(upperLayout,Qt::AlignCenter);

    // Create the back button
    this->backButton = new QPushButton("Back");
    upperLayout->addWidget(this->backButton);
    QObject::connect(this->backButton,&QPushButton::clicked,this,&CaptureWindow::backToMenu);

    // Create the options for the record
    this->recordOptions = new QComboBox();
    this->recordOptions->setStyleSheet("width:200px");

    // Add option for record based on the current fps of the record
    this->recordFPS = 30;
    if(this->FPS == 30){
        this->recordOptions->addItem("1920x1080 30 FPS");
    } else if(this->FPS == 60){
        this->recordOptions->addItem("1920x1080 30 FPS");
        this->recordOptions->addItem("1280x720 60 FPS");
    } else {
        this->recordOptions->addItem("1920x1080 30 FPS");
        this->recordOptions->addItem("1280x720 60 FPS");
        this->recordOptions->addItem("1280x720 120 FPS");
    }
    upperLayout->addWidget(this->recordOptions);

    // Create the record button
    this->recordButton = new QPushButton("Record");
    upperLayout->addWidget(this->recordButton);
    QObject::connect(this->recordButton,&QPushButton::clicked,this,&CaptureWindow::startRecord);

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
    // Terminate the loop for update
    this->isRunning = false;

    // Disconnect all the events for the loop
    QObject::disconnect(this->imgLabel,&CaptureLabel::startCaptureSignal,this,&CaptureWindow::captureImage);
    QObject::disconnect(this->recordButton,&QPushButton::clicked,this,&CaptureWindow::startRecord);
    QObject::disconnect(this->backButton,&QPushButton::clicked,this,&CaptureWindow::backToMenu);
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
    run([=](){
        while(this->isRunning){
            // Capture the frame
            *this->cap >> this->frame;

            //Tracking the points
            for(int i=0;i<this->imgLabel->nPointsSet;i++){
                //run([=](){
                    std::cout<<"Checking: "<<i<<std::endl;
                    // Create the mask
                    Mat hsv;
                    Mat mask;
                    cvtColor(this->frame,hsv,cv::COLOR_BGR2HSV);
                    inRange(hsv,Scalar(this->imgLabel->colorRange[i][LOWER][0],
                            this->imgLabel->colorRange[i][LOWER][1],this->imgLabel->colorRange[i][LOWER][2]),
                            Scalar(this->imgLabel->colorRange[i][UPPER][0],this->imgLabel->colorRange[i][UPPER][1],
                            this->imgLabel->colorRange[i][UPPER][2]),mask);

                    // Find the contours
                    vector<vector<Point>> contours;
                    findContours(mask.clone(),contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);

                    // Find the largest contour
                    double largestArea = -1;
                    int largestContourIndex = -1;
                    for(size_t j=0;j<contours.size();j++){
                        double a = contourArea(contours.at(j));
                        if(a > largestArea){
                            largestArea = a;
                            largestContourIndex = j;
                        }
                    }

                    // Draw the circle and write the details
                    if(largestArea !=-1){
                        std::cout<<largestContourIndex<<std::endl;
                        vector<Point> contourPoly;
                        Point2f center;
                        float radius;

                        approxPolyDP(contours.at(largestContourIndex),contourPoly,3,true);
                        minEnclosingCircle(contourPoly,center,radius);

                        circle(this->frame,center,(int)radius,Scalar(255,255,255),2);
                    }
               //});
            }


            // Pass the frame to the record
            this->recordFrame = new Mat(this->frame);

            // Show the image
            Mat dest;
            cvtColor(this->frame,dest,cv::COLOR_RGB2BGR);
            QImage image = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);

            // Create the image
            this->imgLabel->pixmap = QPixmap::fromImage(image);
            this->imgLabel->changeImage();
            this->imgLabel->frame = new Mat(this->frame);
        }
    });
}
void CaptureWindow::recordImage(){
    run([=]{
        int codec = cv::VideoWriter::fourcc('X','V','I','D');
        std::cout<<this->recordFPS<<std::endl;
        this->videoWriter = new cv::VideoWriter(this->recordFileName,codec,this->recordFPS/5,Size(this->recordWidth,this->recordHeight),true);

        while(this->isRecording){
            if(this->recordFrame){
                Mat *dst = new Mat();
                cvtColor(*this->recordFrame,*dst,cv::COLOR_RGB2BGR);
                cv::resize(*this->recordFrame,*dst,Size(this->recordWidth,this->recordHeight));
                this->videoWriter->write(*dst);
                this->recordFrame = nullptr;
            }
        }
        // Release the video writer
        this->videoWriter->release();
        this->recordFrame = nullptr;
    });
}
void CaptureWindow::startRecord(){
    if(this->isRecording){

        // Turn off the recording
        this->isRecording = false;

        // Change the text to the button
        this->recordButton->setText("Record");

        // Enable the combo box with the fps and dimensions
        this->recordOptions->setEnabled(true);
    } else {
        // Change the text to the button
        this->recordButton->setText("Stop");

        // Get the record frame rage and the width and height
        int idx = this->recordOptions->currentIndex();

        if(idx == 0){
            this->recordFPS = 30;
            this->recordWidth = 1920;
            this->recordHeight = 1080;
        } else if(idx == 1){
            this->recordFPS = 60;
            this->recordWidth = 1280;
            this->recordHeight = 720;
        } else {
            this->recordFPS = 120;
            this->recordWidth = 1280;
            this->recordHeight = 720;
        }

        // Disable the combo box with the fps and dimensions
        this->recordOptions->setEnabled(false);

        // Generate a random string for the video name
        this->recordFileName = generateFileName();
        std::cout<<this->recordFileName<<std::endl;

        // Turn on the recording
        this->isRecording = true;

        recordImage();
    }
}

string CaptureWindow::generateFileName(){
    string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    random_device rd;
    mt19937 generator(rd());
    shuffle(str.begin(),str.end(),generator);
    return str.substr(0,32)+".avi";
}

void CaptureWindow::backToMenu(){
    std::cout<<"Back to menu"<<std::endl;
    this->hide();
    this->isRunning=false;
    this->cap->release();
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}
