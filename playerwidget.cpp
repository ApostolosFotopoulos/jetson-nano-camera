#include "playerwidget.h"

PlayerWidget::PlayerWidget(QMainWindow *parent):QWidget(){
    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    QLabel *label = new QLabel("Player ");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);


    this->setMinimumSize(QSize(960,616));
    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
PlayerWidget::~PlayerWidget(){
    #ifdef LOG
    std::cout<<"PlayerWidget destroyed...."<<std::endl;
    #endif
}
