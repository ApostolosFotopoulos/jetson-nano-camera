#include "launchwidget.h"

LaunchWidget::LaunchWidget(QMainWindow *parent):QWidget(){
    this->parent = parent;

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    QLabel *label = new QLabel("Do you agree with the below origin?");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);

    this->setLayout(mainLayout);
}
LaunchWidget::~LaunchWidget(){

}
