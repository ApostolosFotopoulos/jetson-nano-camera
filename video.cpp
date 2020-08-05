#include "video.h"


Video::Video(QWidget *parent):QWidget(parent){

    // Create the main layout
    QBoxLayout *mainLayout = new QVBoxLayout;

    // Create the player
    this->player = new QMediaPlayer;

    // Create the video widget
    this->videoWidget = new QVideoWidget;

    // Setup the player
    this->player->setVideoOutput(this->videoWidget);
    //this->player->setMedia(QUrl::fromLocalFile("/Users/echatzief/Downloads/video.mp4"));

    //this->player->play();

    // Insert the video widget to the layout
    mainLayout->addWidget(this->videoWidget);

    // Setup the layout to the widget
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

Video::~Video(){

}
QMediaPlayer *Video::getPlayer(){
    return this->player;
}
