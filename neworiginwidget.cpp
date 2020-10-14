#include "neworiginwidget.h"

NewOriginWidget::NewOriginWidget(QMainWindow *parent):QWidget(){
    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    // -------------------------- Create the buttons layout --------------------------//
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->setAlignment(Qt::AlignTop);
    mainLayout->addLayout(buttonsLayout,Qt::AlignTop);

    // -------------------------- Create the buttons --------------------------//

    //- origin
    this->backButton = new QPushButton("Back to menu");
    buttonsLayout->addWidget(this->backButton);
    this->backButton->setStyleSheet("background-color:#686868;");

    // Button events
    QObject::connect(this->backButton,SIGNAL(clicked()),this->parent,SLOT(backToLaunch()));

    this->setMinimumSize(QSize(960,616));
    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
NewOriginWidget::~NewOriginWidget(){
    #ifdef LOG
    std::cout<<"NewOrigin destroyed...."<<std::endl;
    #endif
}
