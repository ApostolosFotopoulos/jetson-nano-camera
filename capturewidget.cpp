#include "capturewidget.h"

CaptureWidget::CaptureWidget(QMainWindow *parent):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    QLabel *label = new QLabel("Capture");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);

    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
CaptureWidget::~CaptureWidget(){
    #ifdef LOG
    std::cout<<"CaptureWidget destroyed...."<<std::endl;
    #endif
}
