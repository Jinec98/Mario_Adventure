#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("://src/images/icon.ico"));

    MainWindow mainWindow;
    mainWindow.setSize();

    mainWindow.show();

    return a.exec();
}
