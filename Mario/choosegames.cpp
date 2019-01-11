#include "choosegames.h"
#include "ui_choosegames.h"

ChooseGames::ChooseGames(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseGames)
{
    ui->setupUi(this);

    typeGroup = new QButtonGroup();
    QString type[] = {"猜数字游戏", "猜拳游戏", "俄罗斯方块", "贪吃蛇"};
    for(int i = 0; i < 4; i++)
    {
        typeButton[i] = new QRadioButton(type[i]);
        typeGroup->addButton(typeButton[i], i);
        typeButton[i]->setGeometry(20, 20+i*40, 160, 20);
        typeButton[i]->setParent(this);
    }
    typeButton[0]->setChecked(true);
    typeButton[0]->setFocus();
}

ChooseGames::~ChooseGames()
{
    delete ui;
}

void ChooseGames::on_buttonBox_clicked(QAbstractButton *button)
{
    int gameType = typeGroup->checkedId();
    switch(gameType)
    {
    case 0:
        guessNum = new GuessNum();
        guessNum->show();
        break;
    case 1:
        guessGesture = new GuessGesture();
        guessGesture->show();
        break;
    case 2:
//        qDebug()<<"tetris";
        tetris = new Tetris();
        tetris->show();
        break;
    case 3:
        snake = new Snake();
        snake->show();
        break;
    }
}
