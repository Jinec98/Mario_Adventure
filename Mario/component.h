#ifndef COMPONENT_H
#define COMPONENT_H


#include <QGraphicsItem>
#include "mainwindow.h"

const int brickType = 1;
const int propBoxType = 2;
const int springType = 3;
const int challengeDoorType = 4;

class Component : public QGraphicsItem
{
public:
    Component(QGraphicsItem *parent = 0);
    virtual void nextFrame() = 0;
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual int type() const = 0;

    enum {Type};
    int currentFrame;
    QPixmap pixmap;
};

class Brick : public Component
{
public:
    Brick(int length, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    enum {Type = brickType};

private:
    int length;
    int direction;
};

class PropBox : public Component
{
public:
    PropBox(int length, int propetyType, QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    enum {Type = propBoxType};
    int propetyType;

private:
    int length;
    int direction;

};

class Spring : public Component
{
public:
    Spring(QGraphicsItem *parent = 0);
    void nextFrame();
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    enum {Type = springType};
};

class ChallengeDoor : public BackgroundItem
{
public:
    ChallengeDoor(QGraphicsItem *parent = 0);
    QRectF boundingRect() const ;
    int type() const;
    enum {Type = challengeDoorType};
};



#endif // COMPONENT_H
