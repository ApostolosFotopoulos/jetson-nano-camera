#include "calibrationwindow.h"

CalibrationWindow::CalibrationWindow(QWidget * parent):QMainWindow(parent){

    // Title of the window
    this->setWindowTitle("Calibration Setup");

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Create the widget for the window
    this->widget = new QWidget(this);

    // Create the main layout
    this->mainLayout = new QVBoxLayout(this->widget);
    this->mainLayout->setAlignment(Qt::AlignVCenter);

    // Set the capture
    Camera c;
    this->cap = new VideoCapture(c.stream(),CAP_GSTREAMER);
    if(!this->cap->isOpened()){
        std::cout<<"Exited"<<std::endl;
        exit(1);
    }

    this->isRunning = true;

    //Create the buttons layout
    this->buttonsLayout = new QHBoxLayout();
    this->buttonsLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->addLayout(this->buttonsLayout,Qt::AlignBottom);

     // Create the buttons and the input
    this->backButton = new QPushButton("Back");
    this->buttonsLayout->addWidget(this->backButton);

    // Input
    this->input = new QLineEdit();
    this->input->setPlaceholderText("Enter the cm for the distance...");
    this->buttonsLayout->addWidget(this->input);

    this->pauseButton = new QPushButton("Pause");
    this->buttonsLayout->addWidget(this->pauseButton);

    this->calButton = new QPushButton("Calibrate");
    this->buttonsLayout->addWidget(this->calButton);

    // Button events
    QObject::connect(this->backButton,&QPushButton::clicked,this,&CalibrationWindow::backToMenu);
    QObject::connect(this->calButton,&QPushButton::clicked,this,&CalibrationWindow::calibrate);
    QObject::connect(this->pauseButton,&QPushButton::clicked,this,&CalibrationWindow::pause);

    //Create the warning layout
    this->warningLayout = new QHBoxLayout();
    this->warningLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->addLayout(this->warningLayout,Qt::AlignBottom);

    // Create the warning label
    this->warningLabel = new QLabel();
    this->warningLabel->setStyleSheet("color:red;");
    this->warningLabel->setText("");
    this->warningLayout->addWidget(this->warningLabel);

    // Create the clickable label for the origin
    this->imgLabel = new CalibrationLabel();
    this->imageLayout = new QHBoxLayout();
    this->imageLayout->addWidget(this->imgLabel);
    this->imageLayout->setAlignment(Qt::AlignCenter);
    this->mainLayout->addLayout(this->imageLayout);
    QObject::connect(this->imgLabel,&CalibrationLabel::startCaptureSignal,this,&CalibrationWindow::captureImage);
    QObject::connect(this->imgLabel,&CalibrationLabel::newPointClicked,this,&CalibrationWindow::renderPoint);
    this->imgLabel->startTheCapture();

    // Set the main layout to window
    this->setCentralWidget(this->widget);
    this->widget->setLayout(this->mainLayout);

    // Set delete on close
    this->setAttribute(Qt::WA_DeleteOnClose);
}
CalibrationWindow::~CalibrationWindow(){
    std::cout<<"Removing resources"<<std::endl;
    // Stop the capturing
    this->isRunning = false;

    // Clean the events
    QObject::disconnect(this->imgLabel,&CalibrationLabel::startCaptureSignal,this,&CalibrationWindow::captureImage);
    QObject::disconnect(this->backButton,&QPushButton::clicked,this,&CalibrationWindow::backToMenu);
    QObject::disconnect(this->calButton,&QPushButton::clicked,this,&CalibrationWindow::calibrate);
    QObject::disconnect(this->pauseButton,&QPushButton::clicked,this,&CalibrationWindow::pause);
    QObject::disconnect(this->imgLabel,&CalibrationLabel::newPointClicked,this,&CalibrationWindow::renderPoint);

    // Delete the pointers
    delete this->cap;
    delete this->imgLabel;
    delete this->backButton;
    delete this->calButton;
    delete this->pauseButton;
    delete this->input;
    delete this->warningLabel;
    delete this->buttonsLayout;
    delete this->warningLayout;
    delete this->imageLayout;
    delete this->mainLayout;
    //delete this->widget;
}
void CalibrationWindow::captureImage(){
    run([=](){
        while(this->isRunning){
            // Capture the frame
            *this->cap >> this->frame;

            // Show the image
            Mat dest;
            cvtColor(this->frame,dest,cv::COLOR_RGB2BGR);
            QImage image1 = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);
            this->imgLabel->setPixmap(QPixmap::fromImage(image1));
        }
        std::cout<<"Out....."<<std::endl;
    });
}
void CalibrationWindow::backToMenu(){
    std::cout<<"Back to menu"<<std::endl;
    this->hide();
    this->isRunning =false;
    this->cap->release();
    MainWindow *w = new MainWindow(this);
    w->show();
    //this->close();
}
bool isNumeric(string str){
    for(unsigned int i=0;i<str.length();i++){
        if(isdigit(str[i]) == false && str[i]!='.' && str[i]!=','){
            return false;
        }
    }
    return true;
}
void CalibrationWindow::calibrate(){
    run([=](){
        std::string in = this->input->text().toStdString();

        // Set the color to red
        this->warningLabel->setStyleSheet("color:red;");

        if(in == ""){
            this->warningLabel->setText("Fill in the cm for the calibration.");
        } else if(!isNumeric(in)){
            this->warningLabel->setText("Wrong type of input. Please enter a number.");
        } else {
            this->warningLabel->setText("");

            // Save the distance to the json
            if(this->imgLabel->p1 && this->imgLabel->p2){
                // Calculate the distance point
                double dist = this->distance(this->imgLabel->p1->x(),this->imgLabel->p1->y(),this->imgLabel->p2->x(),this->imgLabel->p2->y());
                std::cout<<"Distance: "<<dist<<std::endl;

                // Calculate the cm
                double inD;
                std::istringstream(in)>>inD;
                double d = dist/inD;

                QFile file_obj("./params.json");
                if(!file_obj.open(QIODevice::ReadOnly)){
                    std::cout<<"Failed to open ./params.json"<<std::endl;
                    exit(1);
                }

                // Retrieve the json file
                QTextStream file_text(&file_obj);
                QString json_string;
                json_string = file_text.readAll();
                file_obj.close();

                QByteArray json_bytes = json_string.toLocal8Bit();
                auto json_doc=QJsonDocument::fromJson(json_bytes);

                // Change the origins
                auto json_obj=json_doc.object();
                json_obj["distance"] = d;

                QJsonDocument json_doc_1(json_obj);
                json_string = json_doc_1.toJson();

                cout<<"File saved"<<endl;
                QFile save_file("./params.json");
                if(!save_file.open(QIODevice::WriteOnly)){
                    std::cout<< "failed to open save file"<<std::endl;
                    exit(1);
                }
                save_file.write(json_string.toLocal8Bit());
                save_file.close();

                std::string s = "Saved to JSON. 1cm --> "+to_string(d)+" pixels.";
                this->warningLabel->setText(s.c_str());

                // After success set the color to green
                this->warningLabel->setStyleSheet("color:green;");
            } else {
                this->warningLabel->setText("Pause the frame and select two points.");
            }
        }
    });
}
double CalibrationWindow::distance(double x1,double y1,double x2,double y2){
    double x = x1-x2;
    double y = y1-y2;
    double dist = pow(x,2)+pow(y,2);
    return sqrt(dist);
}
void CalibrationWindow::pause(){
    if(this->isRunning){
        this->isRunning = false;
        this->pauseButton->setText("Resume");
        this->imgLabel->isPaused = true;
    } else {

        // Reset the capture
        this->pauseButton->setText("Pause");
        this->isRunning = true;
        this->imgLabel->startTheCapture();
        this->imgLabel->isPaused = false;

        // Reset the point
        this->imgLabel->p1 = nullptr;
        this->imgLabel->p2 = nullptr;
    }
}
void CalibrationWindow::renderPoint(){
    std::cout<<"Render point"<<std::endl;
    if(this->imgLabel->p1){
        drawMarker(this->frame,Point(this->imgLabel->p1->x(),this->imgLabel->p1->y()),Scalar(255,0,0),MARKER_CROSS,10,2);
    }
    if(this->imgLabel->p2){
        drawMarker(this->frame,Point(this->imgLabel->p2->x(),this->imgLabel->p2->y()),Scalar(255,0,0),MARKER_CROSS,10,2);
    }

    // Show the image
    Mat dest;
    cvtColor(this->frame,dest,cv::COLOR_RGB2BGR);
    QImage image1 = QImage((uchar *)dest.data,dest.cols,dest.rows,dest.step,QImage::Format_RGB888);
    this->imgLabel->setPixmap(QPixmap::fromImage(image1));
}
