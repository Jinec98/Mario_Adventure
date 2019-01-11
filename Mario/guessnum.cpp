#include "guessnum.h"

#include "ui_guessnum.h"
#include "ui_guessnumnew.h"

GuessNum::GuessNum(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuessNumWidget)
{
    ui->setupUi(this);
    setWindowTitle(tr("猜数字"));

}



GuessNum::~GuessNum()
{
    delete ui;
}


void GuessNum::on_pushButton_clicked()
{
    win = new GuessNumNewWin();
    win->show();
}

void GuessNum::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/game/src/images/games/pic.jpg"));
}


GuessNumNewWin::GuessNumNewWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuessNumNewWidget)
{
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    int n = qrand()%50;   //生成0-50的数字
    result  = n;

    guesstimes = 5;//最多可猜5次
    tmpnum = 0;
    ui->setupUi(this);

    initWindow();
}

void GuessNumNewWin::initWindow()
{
    setWindowTitle(tr("猜数字"));
    label = new QLabel();
    QFont font("楷体",18,75);
    label->setText("请输入您的数字(0-50)：");
    label->setGeometry(QRect(70,250,400,50));
    label->setParent(this);
    label->setFont(font);
    QPalette palette;

    palette.setColor(QPalette::Background, QColor(0, 255, 0));

    //label->setAutoFillBackground(true);  //一定要这句，否则不行

    //label->setPalette(palette);

    edit = new QLineEdit();
    edit ->setParent(this);
    edit->setGeometry(QRect(150,330,50,50));
    edit->setFont(font);
    edit->setText("0");
    //edit->setAutoFillBackground(true);
    // edit->setPalette(palette);

    btn = new QPushButton();
    btn->setParent(this);
    btn->setGeometry(QRect(500,300,90,50));
    btn->setText(" PK ");


    QIcon icon(":/game/src/images/games/btn.png");

    btn->setIcon(icon);

    btn->setFont(font);
    btn->setFlat(false);


    connect(btn,SIGNAL(clicked()),this,SLOT(computeResult()));

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);

    QFont font1("楷体",20,50);
    labelTitle = new QLabel();
    labelTitle->setGeometry(QRect(85,50,350,150));
    labelTitle->setFont(font1);
    labelTitle->setPalette(pe);
    //labelTitle->setAutoFillBackground(true);  //一定要这句，否则不行
    labelTitle->setParent(this);
    // labelTitle->setPalette(palette);

    labelCom = new QLabel();
    labelCom->setGeometry(QRect(380,150,350,50));
    // labelCom->setAutoFillBackground(true);  //一定要这句，否则不行
    labelCom->setParent(this);
    labelCom->setFont(font);
    //labelCom->setPalette(palette);

}


void GuessNumNewWin::computeResult()
{

    //获取用户输入的数字
    QString input;
    input = edit->text();
    bool ok;
    inputNum = input.toInt(&ok,10);

    QString str = "";
    tmpnum++;
    if(tmpnum<guesstimes)
    {
        if(inputNum==result)
        {
            labelTitle->setText("You Win !!!");
            QString tmpstr = QString::number(result);
            QString st = "";
            st.append("电脑生成的数字为：");
            st.append(tmpstr);
            labelCom->setText(st);
        }
        else if(inputNum > result )
        {
            labelTitle->setText("您输入的数字大了哟~");

            int tmp = guesstimes-tmpnum;
            QString tmpstr = QString::number(tmp);
            str.append("您还剩下");
            str.append(tmpstr);
            str.append("次机会");

            labelCom->setText(str);
        }
        else
            {
            labelTitle->setText("您输入的数字小了哟~");
            int tmp = guesstimes-tmpnum;
            QString tmpstr = QString::number(tmp);
            str.append("您还剩下");
            str.append(tmpstr);
            str.append("次机会");


            labelCom->setText(str);
            }
    }
    else
    {
        labelTitle->setText("You Lose!!");
        labelCom->setText("您的机会已用完");
    }
}

void GuessNumNewWin::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/game/src/images/games/new_pic.jpg"));
}

GuessNumNewWin::~GuessNumNewWin()
{
    delete ui;
}


void GuessNum::on_pushButton_2_clicked()
{
    this->close();
}
