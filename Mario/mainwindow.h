#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPropertyAnimation>
#include <QFont>
#include <QFontDatabase>
#include <QScrollBar>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QWidget>
#include <time.h>
#include <QMessageBox>
#include <QIcon>
#include <QProcess>
#include <QTime>
#include <QLineEdit>
#include <QIcon>

#include "view.h"
#include "title.h"
#include "backgrounditem.h"
#include "player.h"
#include "gamescene.h"
#include "component.h"
#include "property.h"
#include "playerinfo.h"
#include "choosegames.h"
#include "tetris.h"
#include "snake.h"
#include "guessnum.h"
#include "guessgesture.h"

#define WIDTH 1280
#define HEIGHT 720


//namespace Ui {
//class MainWindow;
//}

class Title;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void setSize();
    ~MainWindow();

private:
//    Ui::MainWindow *ui;
    void createScene();

    QRect screenGeometry;
    View *view;
    Title *title;

};

#endif // MAINWINDOW_H
