#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":images/vsimple"));
    w.setWindowTitle("vEdit");
    w.showMaximized();

    return a.exec();
}
