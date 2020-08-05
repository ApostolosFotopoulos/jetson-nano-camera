#include "playercontrols.h"

PlayerControls::PlayerControls(QWidget *parent,QMediaPlayer * player):QWidget(parent){

    // Set the player to local variable
    this->player = player;

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Align the main layout to bottom
    mainLayout->setAlignment(Qt::AlignBottom);

    // Create a group box for the slider
    QGroupBox *gridGroupBoxSlider = new QGroupBox();
    mainLayout->addWidget(gridGroupBoxSlider);

    // Create a horizontal layout for the slider
    QVBoxLayout *sliderLayout = new QVBoxLayout();

    // Create a slider
    this->durationSlider = new QSlider(Qt::Horizontal);
    std::cout<<this->player->duration()<<std::endl;
    this->durationSlider->setRange(0, this->player->duration() /(double) 1000);

    //durationSlider->setStyleSheet("background:transparent;border:none");
    sliderLayout->addWidget(durationSlider);

    // Create the duration label
    this->durationLabel = new QLabel("--:--");
    sliderLayout->addWidget(this->durationLabel);

    // Create the range slider
    this->rangeSlider = new RangeSlider(Qt::Horizontal);
    this->rangeSlider->SetRange(0,this->player->duration() /(double) 1000);
    sliderLayout->addWidget(this->rangeSlider);

    // Set the layout for the slider group box
    gridGroupBoxSlider->setLayout(sliderLayout);

    // Create Group Box for buttons
    QGroupBox *gridGroupBox = new QGroupBox();
    mainLayout->addWidget(gridGroupBox);

    // Create a horizontal layout for the buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    // Align the button layout to the center
    buttonLayout->setAlignment(Qt::AlignHCenter);

    // #####################################  Add the features ################################## //

    // Create the prev button
    QIcon *prevIcon = new QIcon(":/images/return.svg");
    this->prevButton = new QPushButton("");
    //this->prevButton->setStyleSheet("background:transparent;border:none;");
    this->prevButton->setIconSize(QSize(25, 25));
    this->prevButton->setIcon(*prevIcon);
    buttonLayout->addWidget(this->prevButton);

    // Create the pause button
    QIcon *pauseIcon = new QIcon(":/images/pause.svg");
    this->pauseButton = new QPushButton("");
    //this->pauseButton->setStyleSheet("background:transparent;border:none;");
    this->pauseButton->setIconSize(QSize(25, 25));
    this->pauseButton->setIcon(*pauseIcon);
    buttonLayout->addWidget(this->pauseButton);

    // Create the play button
    QIcon *playIcon = new QIcon(":/images/play.svg");
    this->playButton = new QPushButton("");
    //this->playButton->setStyleSheet("background:transparent;border:none;");
    this->playButton->setIconSize(QSize(32, 32));
    this->playButton->setIcon(*playIcon);
    buttonLayout->addWidget(this->playButton);

    // Create the stop button
    QIcon *stopIcon = new QIcon(":/images/stop.svg");
    this->stopButton = new QPushButton("");
    //this->stopButton->setStyleSheet("background:transparent;border:none;");
    this->stopButton->setIconSize(QSize(25, 25));
    this->stopButton->setIcon(*stopIcon);
    buttonLayout->addWidget(this->stopButton);

    // Create the next button
    QIcon *nextIcon = new QIcon(":/images/next.svg");
    this->nextButton = new QPushButton("");
    //this->nextButton->setStyleSheet("background:transparent;border:none;");
    this->nextButton->setIconSize(QSize(25, 25));
    this->nextButton->setIcon(*nextIcon);
    buttonLayout->addWidget(this->nextButton);

    // Create the rate box for the speed
    this->rateBox = new QComboBox(this);
    this->rateBox->setStyleSheet("width:30px;");
    this->rateBox->addItem("0.1x", QVariant(0.1));
    this->rateBox->addItem("0.2x", QVariant(0.2));
    this->rateBox->addItem("0.5x", QVariant(0.5));
    this->rateBox->addItem("1.0x", QVariant(1.0));
    this->rateBox->addItem("2.0x", QVariant(2.0));
    this->rateBox->setCurrentIndex(3);
    buttonLayout->addWidget(this->rateBox);

    // Set the button layout as layout for the grid box
    gridGroupBox->setLayout(buttonLayout);

    // Setup the connect event for the player
    QObject::connect(this->playButton, &QPushButton::clicked,this->player, &QMediaPlayer::play);
    QObject::connect(this->pauseButton, &QPushButton::clicked,this->player, &QMediaPlayer::pause);
    QObject::connect(this->stopButton, &QPushButton::clicked,this->player, &QMediaPlayer::stop);
    QObject::connect(this->rateBox, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);
    QObject::connect(this->player, &QMediaPlayer::durationChanged, this, &PlayerControls::durationChanged);
    QObject::connect(this->player, &QMediaPlayer::positionChanged, this, &PlayerControls::positionChanged);
    QObject::connect(this->nextButton, &QPushButton::clicked, this, &PlayerControls::nextClicked);
    QObject::connect(this->prevButton, &QPushButton::clicked, this, &PlayerControls::prevClicked);
    QObject::connect(this->durationSlider, &QSlider::sliderMoved, this, &PlayerControls::seek);
    QObject::connect(this->rangeSlider, &RangeSlider::lowerValueChanged, this, &PlayerControls::lowerChanged);
    QObject::connect(this->rangeSlider, &RangeSlider::upperValueChanged, this, &PlayerControls::upperChanged);

    // Set the main layout to the window
    this->setLayout(mainLayout);
}
PlayerControls::~PlayerControls(){

    // Disconnect the events
    QObject::disconnect(this->playButton, &QPushButton::clicked,this->player, &QMediaPlayer::play);
    QObject::disconnect(this->pauseButton, &QPushButton::clicked,this->player, &QMediaPlayer::pause);
    QObject::disconnect(this->stopButton, &QPushButton::clicked,this->player, &QMediaPlayer::stop);
    QObject::disconnect(this->rateBox, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);
    QObject::disconnect(this->player, &QMediaPlayer::durationChanged, this, &PlayerControls::durationChanged);
    QObject::disconnect(this->player, &QMediaPlayer::positionChanged, this, &PlayerControls::positionChanged);
    QObject::disconnect(this->nextButton, &QPushButton::clicked, this, &PlayerControls::nextClicked);
    QObject::disconnect(this->prevButton, &QPushButton::clicked, this, &PlayerControls::prevClicked);
    QObject::disconnect(this->durationSlider, &QSlider::sliderMoved, this, &PlayerControls::seek);
    QObject::disconnect(this->rangeSlider, &RangeSlider::lowerValueChanged, this, &PlayerControls::lowerChanged);
    QObject::disconnect(this->rangeSlider, &RangeSlider::upperValueChanged, this, &PlayerControls::upperChanged);
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

    // When the limits are changed
    if((this->duration!=0 && this->duration!=-1) &&(progress/1000 < this->lowerLimit || progress/1000 > this->upperLimit)){
        this->seek(this->lowerLimit);
    } else {
        if(this->duration!=-1 && progress>= this->duration*1000){
            this->durationSlider->setValue(progress / 1000);
            this->player->setPosition(0);
        } else{
            if(!this->durationSlider->isSliderDown())
                this->durationSlider->setValue(progress / 1000);
            updateDurationInfo(progress / 1000);
        }
    }
}
void PlayerControls::nextClicked(){
    if(this->player->position() + 1000 > this->player->duration()){
        this->player->setPosition(this->player->duration());
    } else {
        this->player->setPosition(this->player->position()+1000);
    }
}
void PlayerControls::prevClicked(){
    if(this->player->position() - 1000 < 0){
        this->player->setPosition(0);
    } else {
        this->player->setPosition(this->player->position()-1000);
    }
}
void PlayerControls::seek(int seconds){
    this->player->setPosition(seconds*1000);
}

void PlayerControls::updateDurationInfo(qint64 currentInfo){
    QString tStr;
    if (currentInfo || this->duration!=-1) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((this->duration / 3600) % 60, (this->duration / 60) % 60,
            this->duration % 60, (this->duration * 1000) % 1000);
        QString format = "mm:ss";
        if (this->duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    this->durationLabel->setText(tStr);
}
QSlider * PlayerControls::retrieveSlider(){
    return this->durationSlider;
}
int PlayerControls::retrieveDuration(){
    return this->duration;
}
void PlayerControls::lowerChanged(int val){
    std::cout<<"Lower changed: "<<val<<std::endl;
    this->lowerLimit = val;
    this->player->setPosition(val*1000);
}
void PlayerControls::upperChanged(int val){
    std::cout<<"Upper changed: "<<val<<std::endl;
    this->upperLimit = val;
    this->player->setPosition(val*1000);
}
