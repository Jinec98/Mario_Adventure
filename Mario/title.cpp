#include "title.h"

Title::Title(View *view, QWidget *parent)
    : QGraphicsScene(parent)
    , width(1280)
    , height(720)
{
    viewer = view;
    viewer->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    scroll = new QScrollBar;
    scroll = viewer->horizontalScrollBar();

    backgorundPic = new QGraphicsPixmapItem(QPixmap("://src/images/loginBackpic.jpg"));
    logoPic = new QGraphicsPixmapItem(QPixmap("://src/images/title.png"));
    logoPic->setPos(140, 200);

    addItem(backgorundPic);
    addItem(logoPic);
    this->setFocus();
    this->setSceneRect(0,0,1280,720);
    view->sceneSet(this);



//    backgoundPicture = new QLabel(viewer);
//    backgoundPicture->setPixmap(QPixmap("://src/images/loginBackpic.jpg"));
//    backgoundPicture->setGeometry(0,0,1280,720);

//    title = new QLabel(viewer);
//    title->setPixmap(QPixmap("://src/images/title.png"));
//    title->setGeometry(140, 200, 1000, 120);

    startButton = new QPushButton(viewer);
    //startButton->setText("Start");
    startButton->setObjectName(QString("startButton"));
    startButton->setToolTip("Start Game");
    startButton->setGeometry(QRect(500,400,240,70));
    startButton->setStyleSheet("QPushButton{background-image: url(://src/images/start.png);}");
    startButton->setFlat(true);
    connect(startButton, SIGNAL(clicked()),this,SLOT(startGame()));

    quitButton = new QPushButton(viewer);
    //quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit Game");
    quitButton->setGeometry(QRect(500,500,240,70));
    quitButton->setStyleSheet("QPushButton{background-image: url(://src/images/quit.png);}");
    quitButton->setFlat(true);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(quitGame()));


}

void Title::startGame()
{
    quitButton->close();
    startButton->close();
    scene = new GameScene(scroll, this);
    viewer->sceneSet(scene);

}

void Title::quitGame()
{
    qApp->quit();
}
