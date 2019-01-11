#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
//    ui(new Ui::MainWindow)
{
//    ui->setupUi(this);

    createScene();
    setCentralWidget(view);
    setWindowTitle("Mario Adventure");
    screenGeometry = QApplication::desktop()->screenGeometry();

}

MainWindow::~MainWindow()
{
//    delete ui;
}

void MainWindow::setSize()
{
    this->setFixedSize(1280,720);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

void MainWindow::createScene()
{
    view = new View;
    title = new Title(view);
}
