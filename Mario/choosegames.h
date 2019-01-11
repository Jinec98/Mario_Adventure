#ifndef CHOOSEGAMES_H
#define CHOOSEGAMES_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class ChooseGames;
}

class Tetris;
class Snake;
class GuessNum;
class GuessGesture;
class ChooseGames : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseGames(QWidget *parent = 0);
    ~ChooseGames();
    QButtonGroup *typeGroup;
    QRadioButton *typeButton[4];
//    QString type[4];
    Tetris *tetris;
    Snake *snake;
    GuessNum *guessNum;
    GuessGesture *guessGesture;

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ChooseGames *ui;
};

#endif // CHOOSEGAMES_H
