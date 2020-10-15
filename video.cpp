#include "video.h"


Video::Video(QWidget *parent):QWidget(parent){

    // Create the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);

    // Create the player
    this->player = new QMediaPlayer;

    // Create the video widget
    this->videoWidget = new QVideoWidget;

    // Setup the player
    this->player->setVideoOutput(this->videoWidget);

    // Insert the video widget to the layout
    mainLayout->addWidget(this->videoWidget,Qt::AlignCenter);

    // Setup the layout to the widget
    this->setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

Video::~Video(){

}
QMediaPlayer *Video::getPlayer(){
    return this->player;
}
