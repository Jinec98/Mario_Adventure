#ifndef PROPERTY_H
#define PROPERTY_H

#include <QObject>
#include <QGraphicsItem>
#include "mainwindow.h"

const int coinType = 11;
const int drugType = 12;
const int speedDrugType = 13;
const int jumpDrugType = 14;
const int recoverDrugType = 15;
const int growDrugType = 16;

class Property : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Property(QGraphicsItem *parent = 0);
    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    virtual int type() const = 0;

    enum {Type};
    int currentFrame;
    QPixmap pixmap;

signals:

public slots:
    virtual void nextFrame() = 0;

};

class Coin : public Property
{
    Q_OBJECT
public:
    explicit Coin(QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    enum {Type = coinType};

public slots:
    void nextFrame();
};

class Drug : public Property
{
    Q_OBJECT
public:
    explicit Drug(int drugType, QGraphicsItem *parent = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    int type() const;
    enum {Type = drugType};
    int drugsType;

public slots:
    void nextFrame();
};

class SpeedDrug : public Drug
{
    Q_OBJECT
public:
    explicit SpeedDrug(QGraphicsItem *parent = 0);
    enum {Type = speedDrugType};
};

class JumpDrug : public Drug
{
    Q_OBJECT
public:
    explicit JumpDrug(QGraphicsItem *parent = 0);
    enum {Type = jumpDrugType};
};

class RecoverDrug : public Drug
{
    Q_OBJECT
public:
    explicit RecoverDrug(QGraphicsItem *parent = 0);
    enum {Type = recoverDrugType};
};

class GrowDrug : public Drug
{
    Q_OBJECT
public:
    explicit GrowDrug(QGraphicsItem *parent = 0);
    enum {Type = growDrugType};
};

#endif // PROPERTY_H
