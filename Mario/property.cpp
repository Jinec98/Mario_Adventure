#include "property.h"

Property::Property(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , currentFrame()
{
}


Coin::Coin(QGraphicsItem *parent)
    : Property(parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap("://src/images/coin.png");
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(20);
}

void Coin::nextFrame()
{
    setPos(this->pos().x(),this->pos().y() - 5);
    currentFrame += 38;
    if(currentFrame >= 300)
    {
        delete this;
    }

    //碰撞检测
//    QList<QGraphicsItem *> items = collidingItems();
//    for(int i = 0; i < items.size(); i++)
//    {
//        delete this;
//        return;
//    }
}

QRectF Coin::boundingRect() const
{
    return QRectF(0, 0, 39, 41);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap, currentFrame, 0, 39, 41);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Coin::type() const
{
    return Type;
}

Drug::Drug(int drugType, QGraphicsItem *parent)
    : Property(parent)
    , drugsType(drugType)
{
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(nextFrame()));
    timer->start(100);
}

void Drug::nextFrame()
{
    //碰撞检测
    QList<QGraphicsItem *> items = collidingItems();
    for(int i = 0; i < items.size(); i++)
    {
        delete this;
        return;
    }
}

QRectF Drug::boundingRect() const
{
    return QRectF(0, 0, 29, 42);
}

void Drug::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, pixmap, currentFrame, 0, 29, 42);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Drug::type() const
{
    return Type;
}

SpeedDrug::SpeedDrug(QGraphicsItem *parent)
    : Drug(speedDrugType, parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap(":/src/images/speedDrug.png");
}

JumpDrug::JumpDrug(QGraphicsItem *parent)
    : Drug(jumpDrugType, parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap(":/src/images/jumpDrug.png");
}

RecoverDrug::RecoverDrug(QGraphicsItem *parent)
    : Drug(recoverDrugType, parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap(":/src/images/recoverDrug.png");
}

GrowDrug::GrowDrug(QGraphicsItem *parent)
    : Drug(growDrugType, parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap(":/src/images/growDrug.png");
}

