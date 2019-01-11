#ifndef TITLE_H
#define TITLE_H

#include "mainwindow.h"

class View;
class GameScene;
class Title : public QGraphicsScene
{
     Q_OBJECT

public:
    Title(View *view, QWidget *parent = 0);

private slots:
    void startGame();
    void quitGame();

private:
    int width;
    int height;

    View *viewer;
    GameScene *scene;

    QScrollBar *scroll;
    QGraphicsPixmapItem *backgorundPic;
    QGraphicsPixmapItem *logoPic;
    QPushButton *startButton;
    QPushButton *quitButton;
};

#endif // TITLE_H
