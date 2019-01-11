#include "playerinfo.h"

PlayerInfo::PlayerInfo(int num, QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
    , num(num)
{
    int id = QFontDatabase::addApplicationFont(":/src/font/number.ttf");
    QFontDatabase::applicationFontFamilies(id);
    setPlainText(QString("") + QString::number(num));
    setDefaultTextColor(Qt::black);
    setFont(QFont("CoinCount2",40));
}

void PlayerInfo::increase(int d)
{
    num += d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerInfo::decrease(int d)
{
    num -= d;
    setPlainText(QString("") + QString::number(num));
}


QPainterPath PlayerInfo::shape() const
{
    return QPainterPath();
}

PlayerBlood::PlayerBlood(int num, QGraphicsItem *parent)
    :PlayerInfo(num, parent)
{

}

void PlayerBlood::increase(int d)
{
    num += d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerBlood::decrease(int d)
{
    num -= d;
    setPlainText(QString("") + QString::number(num));
}

QPainterPath PlayerBlood::shape() const
{
    return QPainterPath();
}

PlayerDrug::PlayerDrug(int num, QGraphicsItem *parent)
    :PlayerInfo(num, parent)
{

}

void PlayerDrug::increase(int d)
{
    num += d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerDrug::decrease(int d)
{
    num -= d;
    setPlainText(QString("") + QString::number(num));
}

QPainterPath PlayerDrug::shape() const
{
    return QPainterPath();
}

PlayerCoin::PlayerCoin(int num, QGraphicsItem *parent)
    :PlayerInfo(num, parent)
{

}

void PlayerCoin::increase(int d)
{
    num += d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerCoin::decrease(int d)
{
    num -= d;
    setPlainText(QString("") + QString::number(num));
}

QPainterPath PlayerCoin::shape() const
{
    return QPainterPath();
}

PlayerDamage::PlayerDamage(int num, QGraphicsItem *parent)
    :PlayerInfo(num, parent)
{

}

void PlayerDamage::increase(int d)
{
    num += d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerDamage::decrease(int d)
{
    num -= d;
    setPlainText(QString("") + QString::number(num));
}

void PlayerDamage::setNum(int d)
{
    num = d;
    setPlainText(QString("") + QString::number(num));
}

QPainterPath PlayerDamage::shape() const
{
    return QPainterPath();
}
