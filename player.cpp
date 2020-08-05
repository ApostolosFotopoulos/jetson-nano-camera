#include "player.h"

Player::Player(QWidget *parent): QMainWindow(parent){

    // Set the title of the window
    this->setWindowTitle(QString("Video Player"));

    // Set the window style
    this->setStyleSheet("font-size:15px;background-color:#383838;color:#fff");

    // Create the main widget
    QWidget *widget = new QWidget(this);

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    // Create the player
    this->videoplayer = new Video();

    // Create the toolbar
    this->tools = new Toolbar(widget,this->videoplayer->getPlayer());
    QObject::connect(this->tools, &Toolbar::closeWindow, this, &Player::backToMenu);
    mainLayout->addWidget(this->tools);

    // Add player to layout
    mainLayout->addWidget(this->videoplayer);

    // Create the controls
    this->controls = new PlayerControls(widget,this->videoplayer->getPlayer());
    QObject::connect(this->controls, &PlayerControls::changeRate, this->videoplayer->getPlayer(), &QMediaPlayer::setPlaybackRate);
    mainLayout->addWidget(this->controls);

    // Save some local variables
    this->durationSlider = controls->retrieveSlider();
    this->player = this->videoplayer->getPlayer();

    // Set the main layout to the window
    widget->setLayout(mainLayout);

    // Set to the window the widget as central
    this->setCentralWidget(widget);

    // Set minimum size for the window
    this->setMinimumSize(QSize(960,616));
}

Player::~Player(){
    QObject::disconnect(this->controls, &PlayerControls::changeRate, this->videoplayer->getPlayer(), &QMediaPlayer::setPlaybackRate);
    QObject::disconnect(this->tools, &Toolbar::closeWindow, this, &Player::backToMenu);
}
void Player::backToMenu(){
    std::cout<<"Back to menu"<<std::endl;
    this->hide();
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
}
void Player::wheelEvent(QWheelEvent *event){
    QPoint p = event->pixelDelta();

    // If you scroll up then go back else go forward
    if(p.y() < 0){

        // Get the event from the mouse
        double pos =abs((p.y()/(double)100)*1000);

        if(this->player->position()-pos < 0){
            this->player->setPosition(0);
        } else {
            this->player->setPosition(this->player->position()-pos);
        }
    } else {

        // Get the event from the mouse
        double pos = abs((p.y()/(double)100)*1000);

        if(this->player->position()+pos > this->durationSlider->maximum()*1000){
            this->player->setPosition(this->durationSlider->maximum()*1000);
        } else {
            this->player->setPosition(this->player->position()+pos);
        }
    }
}
