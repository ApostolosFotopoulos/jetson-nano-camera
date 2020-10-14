#include "calibrationwidget.h"

CalibrationWidget::CalibrationWidget(QMainWindow*parent):QWidget(){

    // -------------------------- Setup the parent variable --------------------------//
    this->parent = parent;

    // -------------------------- Create the main layout --------------------------//
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    QLabel *label = new QLabel("Calibration");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);


    this->setMinimumSize(QSize(960,616));
    this->setLayout(mainLayout);
    this->setAttribute(Qt::WA_DeleteOnClose);
}
CalibrationWidget::~CalibrationWidget(){
    #ifdef LOG
    std::cout<<"CalibrationWidget destroyed...."<<std::endl;
    #endif
}
