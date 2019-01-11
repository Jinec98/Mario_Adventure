#include "component.h"

Component::Component(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , currentFrame()
{

}

Brick::Brick(int length, QGraphicsItem *parent)
    : Component(parent)
    , length(length)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap("://src/images/brick.png");
    currentFrame = 0;
}

void Brick::nextFrame()
{
    currentFrame += 50;
    if(currentFrame >= 769)
    {
        currentFrame = 0;
    }
}

QRectF Brick::boundingRect() const
{
    return QRectF(0, 0, 50*length, 50);
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 50*length; i++)
    {
        painter->drawPixmap(i*50, 0, pixmap, currentFrame, 0, 50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Brick::type() const
{
    return Type;
}

PropBox::PropBox(int length, int hasPropetyType, QGraphicsItem *parent)
    : Component(parent)
    , length(length)
    , propetyType(hasPropetyType)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap("://src/images/propBox.png");
    currentFrame = 0;
}

void PropBox::nextFrame()
{
    currentFrame += 50;
    if(currentFrame >= 800)
    {
        currentFrame = 0;
    }
}

QRectF PropBox::boundingRect() const
{
    return QRectF(0, 0, 50*length, 50);
}

void PropBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 50*length; i++)
    {
        painter->drawPixmap(i*50, 0, pixmap, currentFrame, 0, 50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int PropBox::type() const
{
    return Type;
}

Spring::Spring(QGraphicsItem *parent)
    : Component(parent)
{
    setFlag(ItemClipsToShape);
    pixmap = QPixmap(":/src/images/spring.png");
    currentFrame = 0;
}

void Spring::nextFrame()
{

}

QRectF Spring::boundingRect() const
{
    return QRectF(0, 0, 50, 50);
}

void Spring::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    for(int i = 0; i < 50; i++)
    {
        painter->drawPixmap(i*50, 0, pixmap, currentFrame, 0, 50, 50);
    }
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Spring::type() const
{
    return Type;
}

ChallengeDoor::ChallengeDoor(QGraphicsItem *parent)
    : BackgroundItem(QPixmap(":/src/images/challengeDoor.png"),parent)
{

}


QRectF ChallengeDoor::boundingRect() const
{
    return QRectF(0, 0, 100, 121);
}

int ChallengeDoor::type() const
{
    return Type;
}
