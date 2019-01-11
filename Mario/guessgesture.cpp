#include "guessgesture.h"

#include "ui_guessgesture.h"
#include "ui_guessgesturenew.h"

GuessGesture::GuessGesture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuessGestureWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("猜拳"));
}

GuessGesture::~GuessGesture()
{
    delete ui;
}

void GuessGesture::on_pushButton_clicked()
{
     win = new GuessGestureNewWin();
     win->show();
}

void GuessGesture::paintEvent(QPaintEvent *)
{
     QPainter painter(this);
     painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/game/src/images/games/6.png"));
}

void GuessGesture::on_pushButton_2_clicked()
{
     this->close();
}

GuessGestureNewWin::GuessGestureNewWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuessGestureNewWidget)
{
    ui->setupUi(this);
    initWindow();

}

GuessGestureNewWin::~GuessGestureNewWin()
{
    delete ui;
}

void GuessGestureNewWin::outputComGesture()
{
    if(comguesture==1)
         showComGesture->setText("石头（系统）");
    if(comguesture==2)
         showComGesture->setText("剪刀（系统）");
    if(comguesture==3)
         showComGesture->setText("布（系统）");
}

void GuessGestureNewWin::computeResult() //结果检测
{
    outputComGesture();
    if(userGuesture==comguesture)
    {
          label->setText("平局");
    }
    else
        if(userGuesture==1&&comguesture==3||userGuesture==2&&comguesture==1||userGuesture==3&&comguesture==2)
        {
            label->setText("你输了！");
        }
    else
        {
            label->setText("你赢啦！");
        }
}

void GuessGestureNewWin::initWindow()
{
    setWindowTitle(tr("猜拳"));
    QFont font("楷体",18,75);

    btnRock = new QPushButton();
    btnRock->setText("石头");
    btnRock->setGeometry(QRect(70,100,90,50));
    btnRock->setParent(this);
    btnRock->setFont(font);
    QIcon icon1(":/game/src/images/games/石头.png");
    btnRock->setIcon(icon1);

    connect(btnRock,SIGNAL(clicked()),this,SLOT(btnRockClicked()));

    btnScissor = new QPushButton();
    btnScissor->setText("剪刀");
    btnScissor->setGeometry(QRect(70,200,90,50));
    btnScissor->setParent(this);
    btnScissor->setFont(font);
    QIcon icon2(":/game/src/images/games/剪刀.png");
    btnScissor->setIcon(icon2);
    connect(btnScissor,SIGNAL(clicked()),this,SLOT(btnScissorClicked()));

    btnPaper = new QPushButton();
    btnPaper->setText("布");
    btnPaper->setGeometry(QRect(70,300,90,50));
    btnPaper->setParent(this);
    btnPaper->setFont(font);
    QIcon icon3(":/game/src/images/games/布.png");
    btnPaper->setIcon(icon3);
    connect(btnPaper,SIGNAL(clicked()),this,SLOT(btnPaperClicked()));

    btnPk = new QPushButton();
    btnPk->setText("PK");
    btnPk->setGeometry(QRect(300,200,90,50));
    btnPk->setParent(this);
    btnPk->setFont(font);
    QIcon icon4(":/game/src/images/games/pk.png");

    btnPk->setIcon(icon4);
    connect(btnPk,SIGNAL(clicked()),this,SLOT(computeResult()));

    label = new QLabel();
    label->setParent(this);
    label->setFont(font);
    label->setGeometry(QRect(200,100,150,50));

    showComGesture = new QLabel();
    showComGesture->setParent(this);
    showComGesture->setFont(font);
    showComGesture->setGeometry(QRect(315,100,250,50));
}



void GuessGestureNewWin::btnRockClicked()
{
    userGuesture = 1;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n = qrand()%3;   //生成三种手势
    comguesture  = n+1;
}

void GuessGestureNewWin::btnScissorClicked()
{
    userGuesture = 2;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n = qrand()%3;   //生成三种手势
    comguesture  = n+1;
}

void GuessGestureNewWin::btnPaperClicked()
{
    userGuesture = 3;
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n = qrand()%3;   //生成三种手势
    comguesture  = n+1;
}

void GuessGestureNewWin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/game/src/images/games/9.jpg"));
}
