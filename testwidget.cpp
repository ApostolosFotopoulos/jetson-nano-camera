#include "testwidget.h"

TestWidget::TestWidget(QMainWindow *parent):QWidget(){
    this->parent = parent;

    // Create the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignVCenter);

    QLabel *label = new QLabel("Test Widget");
    QHBoxLayout *labelLayout = new QHBoxLayout();
    labelLayout->addWidget(label);
    labelLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(labelLayout);
    this->setLayout(mainLayout);
}
TestWidget::~TestWidget(){

}
