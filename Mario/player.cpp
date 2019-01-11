#include "player.h"

Player::Player(QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , playerState(Standing)
    , playerDirection(0)
    , playerCurrentFrame()
    , playerStandingDirection()
{
    setFlag(ItemClipsToShape);
    standPixmap = QPixmap(":/src/images/stop.png");
    walkPixmap = QPixmap(":/src/images/walk.png");
    playerPixmap = walkPixmap;
}

void Player::stand()
{
    playerPixmap = standPixmap;
    playerCurrentFrame = 0;
    playerState = Standing;
}

void Player::jump()
{
    playerState = Jumping;
}

void Player::walk()
{
    if(playerState == Walking)
        return;

    playerPixmap = walkPixmap;
    playerCurrentFrame = 0;
    playerState = Walking;
}

void Player::fall()
{
    playerState = Falling;
}

bool Player::isFalling()
{
    return playerState == Falling;
}

void Player::nextFrame()
{
    playerCurrentFrame += 57;
    if(playerCurrentFrame >= 1191)
        playerCurrentFrame = 0;
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,45,45);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,playerPixmap,playerCurrentFrame,0,45,45);
    setTransformOriginPoint(boundingRect().center());
    Q_UNUSED(widget);
    Q_UNUSED(option);
}

int Player::direction() const
{
    return playerDirection;
}

void Player::addDirection(int direction)
{
    if(direction == playerDirection)
        return;

    playerDirection += direction;

    if(playerDirection != 0)
    {
        if(playerDirection == -1)
            setTransform(QTransform(-1, 0, 0, 1, boundingRect().width(), 0));
        else
            setTransform(QTransform());
    }
}

int Player::standingDirection() const
{
    return playerStandingDirection;
}

void Player::addStandingDirection(int standingDirection)
{
    playerStandingDirection = standingDirection;
}

bool Player::isTouchingFoot(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) -5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());

    return rect.intersects(otherRect);
}

bool Player::isTouchingHead(QGraphicsItem *item){

    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}

bool Player::isTouchingPlatform(QGraphicsItem *item){

    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}


SpeedPlayer::SpeedPlayer(QGraphicsItem *parent)
    : Player(parent)

{
    setFlag(ItemClipsToShape);
    standPixmap = QPixmap(":/src/images/speedPlayerStop.png");
    walkPixmap = QPixmap(":/src/images/speedPlayerWalk.png");
    playerPixmap = walkPixmap;
}

JumpPlayer::JumpPlayer(QGraphicsItem *parent)
    : Player(parent)

{
    setFlag(ItemClipsToShape);
    standPixmap = QPixmap(":/src/images/jumpPlayerStop.png");
    walkPixmap = QPixmap(":/src/images/jumpPlayerWalk.png");
    playerPixmap = walkPixmap;
}

GrowPlayer::GrowPlayer(QGraphicsItem *parent)
    : Player(parent)

{
    setFlag(ItemClipsToShape);
    standPixmap = QPixmap(":/src/images/growPlayerStop.png");
    walkPixmap = QPixmap(":/src/images/growPlayerWalk.png");
    playerPixmap = walkPixmap;
}

bool Player::isTouchingItemUpper(QGraphicsItem *item)
{
    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), 5);
    return rect.intersects(otherRect);
}

bool Player::isTouchingItemBottom(QGraphicsItem *item)
{
    QRectF rect(pos().x(), pos().y(), boundingRect().width(), 5);
    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
    return rect.intersects(otherRect);
}



//bool Player::isTouchingBody(QGraphicsItem *item)
//{
//    QRectF rect1(pos().x(), pos().y(), 5, boundingRect().height());
//    QRectF rect2(pos().x() + boundingRect().width() - 5, pos().y(), 5, boundingRect().height());
//    QRectF otherRect1(item->pos().x(), item->pos().y(), 5, item->boundingRect().height());
//    QRectF otherRect2(item->pos().x() + item->boundingRect().width() - 5, item->pos().y(), 5, item->boundingRect().height());
//    return rect1.intersects(otherRect1) || rect2.intersects(otherRect2);
//}

//bool Player::isTouchingPlatform(QGraphicsItem *item)
//{
//    QRectF rect(pos().x(), (pos().y() + boundingRect().height()) - 5, boundingRect().width(), 10);
//    QRectF otherRect(item->pos().x(), item->pos().y(), item->boundingRect().width(), item->boundingRect().height());
//    return rect.intersects(otherRect);
//}
