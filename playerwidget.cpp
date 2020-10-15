#include "playerwidget.h"

PlayerWidget::PlayerWidget(QMainWindow *parent):QWidget(){
    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // Create the player
    this->videoplayer = new Video();
    this->player = this->videoplayer->getPlayer();

    // -------------------------- Create the buttons layout --------------------------//
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignTop);

    // -------------------------- Create the buttons --------------------------//

    //- back
    this->backButton = new QPushButton("Back");
    buttonsLayout->addWidget(this->backButton);
    this->backButton->setStyleSheet("background-color:#686868;");

    // open
    this->openButton = new QPushButton("Open");
    buttonsLayout->addWidget(this->openButton);
    this->openButton->setStyleSheet("background-color:#686868;");

    // Image label
    this->fileNameLabel = new QLabel("File: -");
    buttonsLayout->addWidget(this->fileNameLabel,Qt::AlignCenter);


    // Button events
    QObject::connect(this->backButton,SIGNAL(clicked()),this->parent,SLOT(backToLaunch()));
    QObject::connect(this->openButton,SIGNAL(clicked()), this,SLOT(openFile()));

    // Set the upper buttons to the layout
    mainLayout->addLayout(buttonsLayout);

    // Set the player to the layout
    mainLayout->addWidget(this->videoplayer,0);

    // Set the control button to the layout
    mainLayout->addWidget(new PlayerControls(this->videoplayer->getPlayer()),0);

    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
PlayerWidget::~PlayerWidget(){
    #ifdef LOG
    std::cout<<"PlayerWidget destroyed...."<<std::endl;
    #endif
}
void PlayerWidget::openFile(){

   // Create the dialog for file choose
   QFileDialog fileDialog(this);

   // Setting for the file dialog
   fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
   fileDialog.setWindowTitle(tr("Open Files"));
   fileDialog.setNameFilter("*.mp4");
   fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));

   // Save the urls
   if (fileDialog.exec() == QDialog::Accepted){
       QList<QUrl> urls = fileDialog.selectedUrls();
       QUrl current = urls[0];
       std::string fileName = current.toString().toUtf8().constData();
       fileName = fileName.substr(fileName.find_last_of("/") + 1);

       // Set the file name as label
       this->fileNameLabel->setText(QString(fileName.c_str()));

       this->player->setMedia(urls[0]);
       this->player->play();
   }
}
