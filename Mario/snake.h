#ifndef SNAKE_H
#define SNAKE_H

#include "mainwindow.h"

namespace Ui {
class SnakeWidget;
}

class Snake : public QWidget
{
    Q_OBJECT

public:
    explicit Snake(QWidget *parent = 0);
    void init();
    ~Snake();

    void paintEvent(QPaintEvent *event);

    void timerEvent(QTimerEvent *event);

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::SnakeWidget *ui;

    QPoint buf;
    QPoint point;
    QRectF rectangle;

    QPoint body[1024];
    QPoint head_point;
    QPoint food_point;
    int timeid;
    int len;
    int eatflag;
    int direction;//0 w,1 s,2 a,3 d
    int randx,randy;
    int score;
};

#endif // SNAKE_H
