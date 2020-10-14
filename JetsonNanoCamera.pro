#-------------------------------------------------
#
# Project created by QtCreator 2020-10-12T18:50:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets concurrent multimedia multimediawidgets

TARGET = JetsonNanoCamera
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    calibrationwidget.cpp \
    capturewidget.cpp \
        main.cpp \
        mainwindow.cpp \
    launchwidget.cpp \
    camera.cpp \
    neworiginwidget.cpp \
    playerwidget.cpp

HEADERS += \
    calibrationwidget.h \
    capturewidget.h \
        mainwindow.h \
    launchwidget.h \
    camera.h \
    neworiginwidget.h \
    playerwidget.h

INCLUDEPATH += /usr/include/opencv4
#LIBS += -L/usr/lib `pkg-config --libs opencv` -L/usr/include/opencv4 -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_imgproc -lm
