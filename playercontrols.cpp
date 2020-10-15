#include "playercontrols.h"

PlayerControls::PlayerControls(QMediaPlayer * player):QWidget(){

    //Setup the player
    this->player = player;

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignBottom);
    mainLayout->setMargin(0);

    // -------------------------- Slider --------------------------//

    QHBoxLayout *sliderLayout = new QHBoxLayout();
    sliderLayout->setMargin(0);

    this->durationSlider = new QSlider(Qt::Horizontal);
    this->durationSlider->setRange(0, this->player->duration() /(double) 1000);
    sliderLayout->addWidget(this->durationSlider);

    this->durationLabel = new QLabel("--:--");
    sliderLayout->addWidget(this->durationLabel);

    mainLayout->addLayout(sliderLayout);

    this->rangeSlider = new RangeSlider(Qt::Horizontal);
    this->rangeSlider->SetRange(0,this->player->duration() /(double) 1000);
    mainLayout->addWidget(this->rangeSlider);
    // -------------------------- Buttons --------------------------//

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addLayout(buttonLayout);

    // Create the prev button
    QIcon *prevIcon = new QIcon(":/images/return.svg");
    this->prevButton = new QPushButton("");
    this->prevButton->setStyleSheet("background-color:#686868;");
    this->prevButton->setIconSize(QSize(25, 25));
    this->prevButton->setIcon(*prevIcon);
    buttonLayout->addWidget(this->prevButton);

    // Create the pause button
    QIcon *pauseIcon = new QIcon(":/images/pause.svg");
    this->pauseButton = new QPushButton("");
    this->pauseButton->setStyleSheet("background-color:#686868;");
    this->pauseButton->setIconSize(QSize(25, 25));
    this->pauseButton->setIcon(*pauseIcon);
    buttonLayout->addWidget(this->pauseButton);

    // Create the play button
    QIcon *playIcon = new QIcon(":/images/play.svg");
    this->playButton = new QPushButton("");
    this->playButton->setStyleSheet("background-color:#686868;");
    this->playButton->setIconSize(QSize(25,25));
    this->playButton->setIcon(*playIcon);
    buttonLayout->addWidget(this->playButton);

    // Create the stop button
    QIcon *stopIcon = new QIcon(":/images/stop.svg");
    this->stopButton = new QPushButton("");
    this->stopButton->setStyleSheet("background-color:#686868;");
    this->stopButton->setIconSize(QSize(25, 25));
    this->stopButton->setIcon(*stopIcon);
    buttonLayout->addWidget(this->stopButton);

    // Create the next button
    QIcon *nextIcon = new QIcon(":/images/next.svg");
    this->nextButton = new QPushButton("");
    this->nextButton->setStyleSheet("background-color:#686868;");
    this->nextButton->setIconSize(QSize(25, 25));
    this->nextButton->setIcon(*nextIcon);
    buttonLayout->addWidget(this->nextButton);

    this->rateBox = new QComboBox(this);
    this->rateBox->setStyleSheet("background-color:#686868;width:30px;height:32px;");
    this->rateBox->addItem("0.1x", QVariant(0.1));
    this->rateBox->addItem("0.2x", QVariant(0.2));
    this->rateBox->addItem("0.5x", QVariant(0.5));
    this->rateBox->addItem("1.0x", QVariant(1.0));
    this->rateBox->addItem("2.0x", QVariant(2.0));
    this->rateBox->setCurrentIndex(3);
    buttonLayout->addWidget(this->rateBox);

    QObject::connect(this->playButton, &QPushButton::clicked,this->player, &QMediaPlayer::play);
    QObject::connect(this->pauseButton, &QPushButton::clicked,this->player, &QMediaPlayer::pause);
    QObject::connect(this->stopButton, &QPushButton::clicked,this->player, &QMediaPlayer::stop);
    QObject::connect(this->rateBox, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);
    QObject::connect(this, &PlayerControls::changeRate, this->player, &QMediaPlayer::setPlaybackRate);
    QObject::connect(this->player, &QMediaPlayer::durationChanged, this, &PlayerControls::durationChanged);
    //QObject::connect(this->player, &QMediaPlayer::positionChanged, this, &PlayerControls::positionChanged);
    //QObject::connect(this->nextButton, &QPushButton::clicked, this, &PlayerControls::nextClicked);
    //QObject::connect(this->prevButton, &QPushButton::clicked, this, &PlayerControls::prevClicked);


    // Set the main layout to the window
    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
PlayerControls::~PlayerControls(){

}

qreal PlayerControls::playbackRate(){
    return this->rateBox->itemData(this->rateBox->currentIndex()).toDouble();
}
void PlayerControls::updateRate(){
    emit changeRate(playbackRate());
}
void PlayerControls::durationChanged(qint64 duration){
    this->duration = duration/1000;
    this->durationSlider->setMaximum(duration/(double)1000);

    // Setup the limit slider
    this->rangeSlider->SetRange(0,this->duration);
    this->lowerLimit = 0;
    this->upperLimit = this->duration;
}
void PlayerControls::positionChanged(qint64 progress){

}
void PlayerControls::seek(int seconds){

}
void PlayerControls::nextClicked(){

}
void PlayerControls::prevClicked(){

}
void PlayerControls::lowerChanged(int val){

}
void PlayerControls::upperChanged(int val){

}
