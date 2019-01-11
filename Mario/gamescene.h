#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "mainwindow.h"

class Player;
class SpeedPlayer;
class JumpPlayer;
class Brick;
class PropBox;
class Coin;
class Drug;
class SpeedDrug;
class JumpDrug;
class RecoverDrug;
class GrowDrug;
class Spring;
class ChallengeDoor;
class PlayerBlood;
class PlayerDrug;
class PlayerCoin;
class PlayerDamage;
class ChooseGames;
class GameScene : public QGraphicsScene
{
    Q_OBJECT
    Q_PROPERTY(qreal jumpFactor READ jumpFactor WRITE setJumpFactor NOTIFY jumpFactorChanged)
public:
    explicit GameScene(QScrollBar *s, QObject *parent = 0);
    void timerEvent(QTimerEvent *);
    qreal jumpFactor() const;
    void setJumpFactor(const qreal &jumpFactor);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

signals:
    void jumpFactorChanged(qreal);
    //void spawnCoin();

private slots:
    void movePlayer();
    void jumpPlayer();
    void fallPlayer();
    void changePlayer();
    void checkTimer();
    void checkCollidingPropBox();
    void checkCollidingDrug();
    void checkCollidingSpring();
    void checkCollidingChallengeDoor();
    void checkNotCollidingChallengeDoor();

    void controlPropBox(PropBox *propBox);

    bool handleCollisionWithPlatform();
    QGraphicsItem* collidingPlatforms();
    void jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);


private:
    void initGameScene();

    int sceneWidth;//游戏虚拟宽度
    int groundLevel;//地平面
    int velocity;//速度
    int jumpHeight;//跳跃高度
    int fallSpeed;//下落速度
    bool falling;
    bool jumping;
    bool touchedSpring;
    bool touchedSpringButton;
    bool touchedChallengeDoor;
    qreal playerJumpFactor;

    QScrollBar *scroll;
    QTimer timer;
    QTimer fallTimer;
    QTimer *changeTimer;
    QPropertyAnimation *jumpAnimation;
    QGraphicsItem *platfrom;

    PlayerBlood *bloodInfo;
    PlayerDrug *drugInfo;
    PlayerCoin *coinInfo;
    PlayerDamage *damageInfo;

    BackgroundItem *groundItem;
    BackgroundItem *backgroundPic;
    BackgroundItem *bloodLogo;
    BackgroundItem *drugLogo;
    BackgroundItem *coinLogo;
    BackgroundItem *damageLogo;


    Player *player;
//    SpeedPlayer *speedPlayer;
//    JumpPlayer *jumpPlayer;
    Brick *brick1;
    Brick *brick2;
    Brick *brick3;
    PropBox *propBox1;
    PropBox *propBox2;
    PropBox *propBox3;
    PropBox *propBox4;
    PropBox *propBox5;
    Coin *coin1;
    SpeedDrug *speedDrug1;
    JumpDrug *jumpDrug1;
    RecoverDrug *recoverDrug1;
    GrowDrug *growDrug1;
    Spring *spring1;
    ChallengeDoor *challengeDoor1;

    ChooseGames *chooseGameWin;

};

#endif // GAMESCENE_H
