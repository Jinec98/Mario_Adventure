#ifndef GUESSNUM_H
#define GUESSNUM_H

#include "mainwindow.h"

namespace Ui {
class GuessNumWidget;
class GuessNumNewWidget;
}
class GuessNumNewWin;
class GuessNum : public QWidget
{
    Q_OBJECT

public:
    explicit GuessNum(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~GuessNum();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::GuessNumWidget *ui;
    GuessNumNewWin *win;
};


class GuessNumNewWin : public QWidget
{
    Q_OBJECT

public:
    explicit GuessNumNewWin(QWidget *parent = 0);
    ~GuessNumNewWin();
    void paintEvent(QPaintEvent *);
    void initWindow();


private:
    Ui::GuessNumNewWidget *ui;
    QLabel *label;
    QPushButton *btn;
    QLineEdit *edit;
    QLabel *labelTitle;
    QLabel *labelCom;//电脑生成的数字
    int comNum;
    int inputNum;
    int result;
    int tempnum;
    int guesstimes; //最多可供猜测次数
    int tmpnum;
public slots:
    void computeResult();
};

#endif // GUESSNUM_H
