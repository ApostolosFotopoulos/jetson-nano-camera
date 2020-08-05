#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>
#include <QStandardPaths>
#include <QList>
#include <QMediaPlayer>
#include <QLabel>

class Toolbar:public QWidget
{
    Q_OBJECT
public:
    Toolbar(QWidget *parent = nullptr,QMediaPlayer * player=nullptr);
    ~Toolbar();
private slots:
    void openFile();
    void backToMenu();
signals:
    void closeWindow();
private:
    QPushButton *openButton=nullptr;
    QPushButton *backButton=nullptr;
    QLabel *fileNameLabel=nullptr;
    QMediaPlayer * player;
};

#endif // TOOLBAR_H
