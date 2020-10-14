#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_SCALE_FACTOR", "1");
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
