#include "toolbar.h"

Toolbar::Toolbar(QWidget *parent,QMediaPlayer * player):QWidget(parent){

    // Setup the player
    this->player = player;

    // Create the main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    // Create a group box for the tools
    QGroupBox *gridGroupBox = new QGroupBox();
    mainLayout->addWidget(gridGroupBox);

    // Create the button layout to add to the grid box
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignLeft);

    // Create the back button
    this->backButton = new QPushButton(this);
    this->backButton->setText("Back");
    this->backButton->setCheckable(true);
    //openButton->setStyleSheet("background:#fff;color:black;border:1px solid #fff;padding:2%;border-radius:2px;");
    this->backButton->setEnabled(true);
    buttonsLayout->addWidget(this->backButton);

    // Create the open button
    this->openButton = new QPushButton(this);
    this->openButton->setText("Open");
    this->openButton->setCheckable(true);
    //openButton->setStyleSheet("background:#fff;color:black;border:1px solid #fff;padding:2%;border-radius:2px;");
    this->openButton->setEnabled(true);
    buttonsLayout->addWidget(this->openButton);

    // Create the label with the name
    this->fileNameLabel = new QLabel("File: -");
    buttonsLayout->addWidget(this->fileNameLabel);

    // Add buttons layout to the grid box
    gridGroupBox->setLayout(buttonsLayout);

    // Align the main layout to bottom
    mainLayout->setAlignment(Qt::AlignTop);

    // Connect the button event with the slot
    QObject::connect(this->openButton, &QPushButton::clicked, this, &Toolbar::openFile);
    QObject::connect(this->backButton, &QPushButton::clicked, this, &Toolbar::backToMenu);
}
Toolbar::~Toolbar(){
    // Disconnect the events
    QObject::disconnect(this->openButton, &QPushButton::clicked, this, &Toolbar::openFile);
    QObject::disconnect(this->backButton, &QPushButton::clicked, this, &Toolbar::backToMenu);
}
void Toolbar::openFile(){

    // Create the dialog for file choose
    QFileDialog fileDialog(this);

    // Setting for the file dialog
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    fileDialog.setNameFilter("*.avi");
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
    }
}

void Toolbar::backToMenu(){
    emit closeWindow();
}
