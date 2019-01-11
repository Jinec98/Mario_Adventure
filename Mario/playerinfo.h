#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include "mainwindow.h"

class PlayerInfo : public QGraphicsTextItem
{
public:
    PlayerInfo(int num, QGraphicsItem * parent=0);
    void increase(int d);
    void decrease(int d);
    int num;
    virtual QPainterPath shape() const;
};

class PlayerBlood : public PlayerInfo
{
public:
    PlayerBlood(int num, QGraphicsItem * parent=0);
    void increase(int d);
    void decrease(int d);
    QPainterPath shape() const;
};

class PlayerDrug : public PlayerInfo
{
public:
    PlayerDrug(int num, QGraphicsItem * parent=0);
    void increase(int d);
    void decrease(int d);
    QPainterPath shape() const;
};

class PlayerCoin : public PlayerInfo
{
public:
    PlayerCoin(int num, QGraphicsItem * parent=0);
    void increase(int d);
    void decrease(int d);
    QPainterPath shape() const;
};

class PlayerDamage : public PlayerInfo
{
public:
    PlayerDamage(int num, QGraphicsItem * parent=0);
    void increase(int d);
    void decrease(int d);
    void setNum(int d);
    QPainterPath shape() const;
};


#endif // PLAYERINFO_H
