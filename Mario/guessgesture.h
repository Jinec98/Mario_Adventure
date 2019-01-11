#ifndef GUESSGESTURE_H
#define GUESSGESTURE_H

#include "mainwindow.h"

namespace Ui {
class GuessGestureWidget;
class GuessGestureNewWidget;
}

class GuessGestureNewWin;
class GuessGesture : public QWidget
{
    Q_OBJECT

public:
    explicit GuessGesture(QWidget *parent = 0);
    ~GuessGesture();
     void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();


private:
    Ui::GuessGestureWidget *ui;
    GuessGestureNewWin *win;
};

class GuessGestureNewWin : public QWidget
{
    Q_OBJECT

public:
    explicit GuessGestureNewWin(QWidget *parent = 0);
    ~GuessGestureNewWin();
    void initWindow();
    //void computeResult();
    void formatGesture();
    void outputComGesture();
    void paintEvent(QPaintEvent *);
private:
    Ui::GuessGestureNewWidget *ui;
    QPushButton *btnRock ;
    QPushButton *btnPaper;
    QPushButton *btnScissor;
    QPushButton *btnPk;
    QLabel *label;
    QLabel *showComGesture;
    int userGuesture ;//标记用户输入的手势，1表示石头
              //2表示剪刀，3表示布
    int comguesture;//标记电脑生成的手势

public slots:
    void btnRockClicked();
    void btnPaperClicked();
    void btnScissorClicked();
    void computeResult();

};

#endif // GUESSGESTURE_H
