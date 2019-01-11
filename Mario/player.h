#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include "mainwindow.h"

class Player : public QGraphicsItem
{
public:
    Player(QGraphicsItem *parent = 0);

    void stand();
    void jump();
    void walk();
    void fall();
    bool isFalling();

    int direction() const;
    void addDirection(int direction);
    int standingDirection() const;
    void addStandingDirection(int standingDirection);

    void nextFrame();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool isTouchingFoot(QGraphicsItem *item);
    bool isTouchingHead(QGraphicsItem *item);
    bool isTouchingBody(QGraphicsItem *item);
    bool isTouchingItemUpper(QGraphicsItem *item);
    bool isTouchingItemBottom(QGraphicsItem *item);
    bool isTouchingPlatform(QGraphicsItem *item);

    enum State
    {
        Standing = 0,
        Walking,
        Jumping,
        Falling,
    };

    QPixmap playerPixmap;
    QPixmap standPixmap;
    QPixmap walkPixmap;
//    QPixmap jumpPixmap;

    State playerState;

    int playerCurrentFrame;
    int playerDirection;
    int playerStandingDirection;
};

class SpeedPlayer : public Player
{
public:
    SpeedPlayer(QGraphicsItem *parent = 0);
};

class JumpPlayer : public Player
{
public:
    JumpPlayer(QGraphicsItem *parent = 0);
};

class GrowPlayer : public Player
{
public:
    GrowPlayer(QGraphicsItem *parent = 0);
};
#endif // PLAYER_H
