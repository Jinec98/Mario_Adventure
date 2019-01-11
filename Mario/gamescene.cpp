#include "gamescene.h"

GameScene::GameScene(QScrollBar * s, QObject *parent) :
    QGraphicsScene(0,0,8000,720,parent)
  , sceneWidth(8000)
  , groundLevel(660)
  , scroll(s)
  , platfrom()
  , velocity(7)
  , jumpHeight(200)
  , fallSpeed(30)
  , jumpAnimation(new QPropertyAnimation(this))
  , player()
  , touchedSpring(false)
  , touchedChallengeDoor(false)
{
    initGameScene();

    timer.setInterval(20);
    connect(&timer, &QTimer::timeout,this,&GameScene::movePlayer);
    fallTimer.setInterval(20);
    connect(&fallTimer,&QTimer::timeout,this,&GameScene::fallPlayer);

    changeTimer = new QTimer(this);
    connect(changeTimer,&QTimer::timeout,this,&GameScene::changePlayer);

    jumpAnimation->setTargetObject(this);
    jumpAnimation->setPropertyName("jumpFactor");
    jumpAnimation->setStartValue(0);
    jumpAnimation->setKeyValueAt(0.5,1);
    jumpAnimation->setEndValue(0);
    jumpAnimation->setDuration(800);
    jumpAnimation->setEasingCurve(QEasingCurve::OutInQuad);

    connect(this,&GameScene::jumpFactorChanged,this,&GameScene::jumpPlayer);
    connect(jumpAnimation,&QPropertyAnimation::stateChanged,this,&GameScene::jumpStatusChanged);

    //connect(this, SIGNAL(spawnCoin()), this, SLOT(controlPropBox()));

    falling = false;
    jumping = false;
    player->addStandingDirection(1);
}

//初始化游戏窗口
void GameScene::initGameScene()
{
    setSceneRect(0,0,sceneWidth,720);

    //添加背景图片
    backgroundPic = new BackgroundItem(QPixmap("://src/images/sky.png"));
    backgroundPic->setPos(0, 0);
    addItem(backgroundPic);

    //添加Logo
    bloodLogo = new BackgroundItem(QPixmap("://src/images/blood.png"));
    bloodLogo->setPos(30, 30);
    addItem(bloodLogo);
    drugLogo = new BackgroundItem(QPixmap("://src/images/drug.png"));
    drugLogo->setPos(200, 30);
    addItem(drugLogo);
    coinLogo = new BackgroundItem(QPixmap("://src/images/count.png"));
    coinLogo->setPos(400, 30);
    addItem(coinLogo);
    damageLogo = new BackgroundItem(QPixmap("://src/images/sword.png"));
    damageLogo->setPos(600, 30);
    addItem(damageLogo);


    //添加地面
    groundItem = new BackgroundItem(QPixmap("://src/images/ground.png"));
    groundItem->setPos(0, groundLevel);
    addItem(groundItem);

    //添加挑战门
    challengeDoor1 = new ChallengeDoor();
    challengeDoor1->setPos(1450, groundLevel - challengeDoor1->boundingRect().height()-300);
    addItem(challengeDoor1);

    //添加人物
    player = new Player();
    player->setPos(50,groundLevel - player->boundingRect().height());
    addItem(player);
    //player->stand();

    //添加信息
    bloodInfo = new PlayerBlood(50);
    bloodInfo->setPos(80,25);
    addItem(bloodInfo);
    drugInfo = new PlayerDrug(0);
    drugInfo->setPos(250,25);
    addItem(drugInfo);
    coinInfo = new PlayerCoin(0);
    coinInfo->setPos(450,25);
    addItem(coinInfo);
    damageInfo = new PlayerDamage(2);
    damageInfo->setPos(650,25);
    addItem(damageInfo);

    //添加砖块
    brick1 = new Brick(15);
    brick1->setPos(400, groundLevel - brick1->boundingRect().height() - 100);
    addItem(brick1);
    brick2 = new Brick(3);
    brick2->setPos(700, groundLevel - brick2->boundingRect().height() - 250);
    addItem(brick2);
    brick3 = new Brick(6);
    brick3->setPos(1350, groundLevel - brick3->boundingRect().height() - 250);
    addItem(brick3);

    //添加道具箱
    propBox1 = new PropBox(1,coinType);
    propBox1->setPos(200, groundLevel - propBox1->boundingRect().height() - 100);
    addItem(propBox1);
    propBox2 = new PropBox(1,speedDrugType);
    propBox2->setPos(450, groundLevel - propBox2->boundingRect().height() - 250);
    addItem(propBox2);
    propBox3 = new PropBox(1,jumpDrugType);
    propBox3->setPos(650, groundLevel - propBox3->boundingRect().height() - 250);
    addItem(propBox3);
    propBox4 = new PropBox(1,recoverDrugType);
    propBox4->setPos(850, groundLevel - propBox4->boundingRect().height() - 250);
    addItem(propBox4);
    propBox5 = new PropBox(1,growDrugType);
    propBox5->setPos(1050, groundLevel - propBox5->boundingRect().height() - 250);
    addItem(propBox5);

    //添加弹簧
    spring1 = new Spring();
    spring1->setPos(1700, groundLevel - spring1->boundingRect().height());
    addItem(spring1);


}

//按键事件
void GameScene::keyPressEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch(event->key())
    {
    case Qt::Key_Right:
        player->addDirection(1);
        player->addStandingDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        player->addDirection(-1);
        player->addStandingDirection(-1);
        checkTimer();
        break;
    case Qt::Key_Space:
        if(fallTimer.isActive())
            return;
        else if(touchedChallengeDoor)
            return;
//        else if(touchedSpringButton)
//            return;
        else
        {
            if(jumpAnimation->state() == QAbstractAnimation::Stopped)
            {
                jumpAnimation->start();
            }
        }
        break;
    case Qt::Key_F:
        if(!touchedChallengeDoor)
            return;
        qDebug()<<"wo an le F";

        if( player->playerDirection == 1)
            player->addDirection(-1);
        else if( player->playerDirection == -1)
            player->addDirection(1);
        checkTimer();

        chooseGameWin = new ChooseGames();
        chooseGameWin->show();
        break;
    default:
        break;
    }
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if(event->isAutoRepeat())
        return;

    switch(event->key())
    {
    case Qt::Key_Right:
        player->addDirection(-1);
//        player->addStandingDirection(1);
        checkTimer();
        break;
    case Qt::Key_Left:
        player->addDirection(1);
//        player->addStandingDirection(-1);
        checkTimer();
        break;
    default:
        break;
    }
}

void GameScene::checkTimer()
{
    if(player->direction() == 0)
    {
        player->stand();
        timer.stop();
    }
    else if(!timer.isActive())
    {
        timer.start();
        player->walk();
    }
}

void GameScene::movePlayer()
{
    //碰撞检测
//    checkCollidingPropBox();
    checkCollidingDrug();
    checkCollidingSpring();
    checkCollidingChallengeDoor();
    checkNotCollidingChallengeDoor();

    if(player->isFalling())
        return;

    player->nextFrame();
    int direction = player->direction();
    if(direction == 0)
        return;

    if(!(platfrom && player->isTouchingPlatform(platfrom)) && jumpAnimation->state() == QAbstractAnimation::Stopped)
    {
        if(platfrom)
        {
//            qDebug()<<"111";
            player->fall();
            fallTimer.start();
        }
    }

    const int dx = direction * velocity;
    if(direction > 0)
    {
        if(player->pos().x() >= sceneWidth - player->boundingRect().width())
            return;

        player->moveBy(dx,0);
        int diff = player->pos().x() - scroll->value();

        if(diff > 800)
        {
            if(scroll->value() > sceneWidth - WIDTH)
                return;

            scroll->setValue(dx + scroll->value());
            //重新设置界面坐标
            backgroundPic->setPos(dx + backgroundPic->pos().x(), backgroundPic->pos().y());
            bloodLogo->setPos(dx + bloodLogo->pos().x(), bloodLogo->pos().y());
            drugLogo->setPos(dx + drugLogo->pos().x(), drugLogo->pos().y());
            coinLogo->setPos(dx + coinLogo->pos().x(), coinLogo->pos().y());
            damageLogo->setPos(dx + damageLogo->pos().x(), damageLogo->pos().y());
            bloodInfo->setPos(dx + bloodInfo->pos().x(), bloodInfo->pos().y());
            drugInfo->setPos(dx + drugInfo->pos().x(), drugInfo->pos().y());
            coinInfo->setPos(dx + coinInfo->pos().x(), coinInfo->pos().y());
            damageInfo->setPos(dx + damageInfo->pos().x(), damageInfo->pos().y());

        }
    }
    if(direction < 0)
    {
        if(player->pos().x() < 0)
            return;

        player->moveBy(dx,0);
        int diff2 = player->pos().x() - scroll->value();

        if(diff2 < 600)
        {
            if(backgroundPic->pos().x() <= 0)
                return;

            qDebug()<<"move left";
            scroll->setValue(dx + scroll->value());
            //重新设置界面坐标
            backgroundPic->setPos(dx + backgroundPic->pos().x(), backgroundPic->pos().y());
            bloodLogo->setPos(dx + bloodLogo->pos().x(), bloodLogo->pos().y());
            drugLogo->setPos(dx + drugLogo->pos().x(), drugLogo->pos().y());
            coinLogo->setPos(dx + coinLogo->pos().x(), coinLogo->pos().y());
            damageLogo->setPos(dx + damageLogo->pos().x(), damageLogo->pos().y());
            bloodInfo->setPos(dx + bloodInfo->pos().x(), bloodInfo->pos().y());
            drugInfo->setPos(dx + drugInfo->pos().x(), drugInfo->pos().y());
            coinInfo->setPos(dx + coinInfo->pos().x(), coinInfo->pos().y());
            damageInfo->setPos(dx + damageInfo->pos().x(), damageInfo->pos().y());
        }
    }
}

void GameScene::jumpStatusChanged(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(newState == QAbstractAnimation::Stopped && oldState == QAbstractAnimation::Running){
//        handleCollisionWithPlatform();
//        if(touchedSpring)
//        {
//            jumpHeight = 200;
//            touchedSpring = false;
//        }
    }
}

void GameScene::fallPlayer()
{
//    //碰撞检测
//    checkCollidingPropBox();
    checkCollidingDrug();
//    checkCollidingSpring();
//    checkCollidingChallengeDoor();
//    checkNotCollidingChallengeDoor();


    player->setPos(player->pos().x(), player->pos().y() + fallSpeed);
    QGraphicsItem *item = collidingPlatforms();
    //下落时碰撞
    if(item && handleCollisionWithPlatform())
    {
//        checkCollidingDrug();
        qDebug()<<"123";
        fallTimer.stop();
        player->walk();
    }
    else if(player->pos().y() + player->boundingRect().height() >= groundLevel)
    {
        player->setPos(player->pos().x(), groundLevel - player->boundingRect().height());
        fallTimer.stop();
        player->walk();
        platfrom = 0;
        if(touchedSpring)
        {
            qDebug()<<"change height";
            jumpHeight = 200;
            touchedSpring = false;
        }
    }

}

void GameScene::jumpPlayer()
{
    //碰撞检测
    checkCollidingPropBox();
    checkCollidingDrug();
    checkCollidingSpring();
    checkCollidingChallengeDoor();
    checkNotCollidingChallengeDoor();

    if(jumpAnimation->state() == QAbstractAnimation::Stopped)
    {
        player->stand();
        return;
    }

    QGraphicsItem *item = collidingPlatforms();
    if(item)
    {
        if(player->isTouchingHead(item))
        {
            jumpAnimation->stop();
            fallTimer.start();
            return;
        }
        else
        {
            //跳跃到一半碰撞
            if(handleCollisionWithPlatform())
            {
//                checkCollidingDrug();
//                qDebug()<<"312";
                jumpAnimation->stop();
                player->walk();
                return;
            }

        }
    }

    if(fallTimer.isActive())
        return;

    qreal y = (groundLevel - player->boundingRect().height()) - jumpAnimation->currentValue().toReal() * jumpHeight;
    if(platfrom)
    {
        y = (platfrom->pos().y() - player->boundingRect().height() - jumpAnimation->currentValue().toReal() * jumpHeight);
        if(!(platfrom && player->isTouchingPlatform(platfrom)) && playerJumpFactor < 0.1)
        {
            //走出构件边界自由下落
            if((player->pos().x() + player->boundingRect().width() < platfrom->pos().x()) || (player->pos().x() > platfrom->pos().x() + platfrom->boundingRect().width()))
            {
//                if(!platfrom)
//                    platfrom = 0;
                if(player->pos().y() < groundLevel)
                {
                    player->fall();
                    fallTimer.start();
                    return;
                }
            }
        }
    }
    player->setPos(player->pos().x(), y);
}

//jumpFactor跳跃高度比
qreal GameScene::jumpFactor() const
{
    return playerJumpFactor;
}

void GameScene::setJumpFactor(const qreal &jumpFactor)
{
    if(playerJumpFactor == jumpFactor)
        return;
    //qDebug()<<playerJumpFactor;
    playerJumpFactor = jumpFactor;
    emit jumpFactorChanged(playerJumpFactor);
}

void GameScene::changePlayer()
{
//    qDebug()<<"123";
    removeItem(player);
    qreal x = player->pos().x();
    qreal y = player->pos().y();
    int playerDirection = player->playerDirection;
    int playerStandingDirection = player->playerStandingDirection;
    player = new Player();

    if(playerDirection == 1)
        player->addDirection(1);
    else if(playerDirection == -1)
        player->addDirection(-1);

    if(playerStandingDirection == 1)
        player->addStandingDirection(1);
    else if(playerStandingDirection == -1)
    {
        player->addStandingDirection(-1);
        player->setTransform(QTransform(-1, 0, 0, 1, player->boundingRect().width(), 0));
    }

    player->setPos(x, y);
    addItem(player);

    velocity = 7;
    jumpHeight = 200;
    damageInfo->setNum(2);
    changeTimer->stop();
}

//各个构件动作事件
void GameScene::timerEvent(QTimerEvent *)
{
    brick1->nextFrame();
    propBox1->nextFrame();
}

void GameScene::controlPropBox(PropBox *propBox)
{
    if(propBox->propetyType == coinType)
    {
        coin1 = new Coin();
        coin1->setPos(propBox->pos().x() + 5, propBox->pos().y() - coin1->boundingRect().height());
        addItem(coin1);
        //coinInfo->increse(1);
    }
    else if(propBox->propetyType == speedDrugType)
    {
        speedDrug1 = new SpeedDrug();
        speedDrug1->setPos(propBox->pos().x() + 10, propBox->pos().y() - speedDrug1->boundingRect().height());
        addItem(speedDrug1);

    }
    else if(propBox->propetyType == jumpDrugType)
    {
        jumpDrug1 = new JumpDrug();
        jumpDrug1->setPos(propBox->pos().x() + 10, propBox->pos().y() - jumpDrug1->boundingRect().height());
        addItem(jumpDrug1);

    }
    else if(propBox->propetyType == recoverDrugType)
    {
        recoverDrug1 = new RecoverDrug();
        recoverDrug1->setPos(propBox->pos().x() + 10, propBox->pos().y() - recoverDrug1->boundingRect().height());
        addItem(recoverDrug1);

    }
    else if(propBox->propetyType == growDrugType)
    {
        growDrug1 = new GrowDrug();
        growDrug1->setPos(propBox->pos().x() + 10, propBox->pos().y() - growDrug1->boundingRect().height());
        addItem(growDrug1);

    }


}

//碰撞检测

QGraphicsItem * GameScene::collidingPlatforms()
{
    QList<QGraphicsItem *> items = collidingItems(player);
    foreach(QGraphicsItem *item, items)
    {
        if(Brick *brick = qgraphicsitem_cast<Brick *>(item))
        {
            return brick;
        }
        else if(PropBox *propBox = qgraphicsitem_cast<PropBox *>(item))
        {
            return propBox;
        }
        else if(Spring *spring = qgraphicsitem_cast<Spring *>(item))
        {
            return spring;
        }
        else if(Drug *drug = qgraphicsitem_cast<Drug *>(item))
        {
            return drug;
        }
    }
    return 0;
}

bool GameScene::handleCollisionWithPlatform()
{
    QList<QGraphicsItem *> items = collidingItems(player);
    foreach(QGraphicsItem *item, items)
    {
        if(qgraphicsitem_cast<Spring *>(item))
        {
            if(player->isTouchingFoot(item))
            {
                if(player->isTouchingItemUpper(item))
                    checkCollidingSpring();
                qDebug()<<"321";

                jumpHeight = 300;
                touchedSpring = true;

                player->setPos(player->pos().x(), item->pos().y() - player->boundingRect().height());
                this->platfrom = item;
                jumpAnimation->stop();
                //jumpHeight -= 100;

            }
            return true;

        }
        else if(qgraphicsitem_cast<Drug *>(item))
        {
            this->platfrom = 0;
            checkCollidingDrug();

            if(touchedSpring)
            {
                qDebug()<<"change height";
                jumpHeight = 200;
                touchedSpring = false;
            }
            return false;
        }
        else if(qgraphicsitem_cast<QGraphicsTextItem *>(item))
        {
            this->platfrom = 0;

            if(touchedSpring)
            {
                qDebug()<<"change height";
                jumpHeight = 200;
                touchedSpring = false;
            }
            return false;
        }

    }


    QGraphicsItem *platfrom = collidingPlatforms();
    if(platfrom)
    {
        QPointF platfromPos = platfrom->pos();
        if(player->isTouchingFoot(platfrom))
        {
//            qDebug()<<"321";
            player->setPos(player->pos().x(), platfromPos.y() - player->boundingRect().height());
            this->platfrom = platfrom;
            jumpAnimation->stop();

            if(touchedSpring)
            {
                qDebug()<<"change height";
                jumpHeight = 200;
                touchedSpring = false;
            }
            return true;
        }
    }
    else
    {
        if(touchedSpring)
        {
            qDebug()<<"change height";
            jumpHeight = 200;
            touchedSpring = false;
        }
        this->platfrom = 0;
    }
    return false;

}

//与道具箱碰撞
void GameScene::checkCollidingPropBox()
{
    QList<QGraphicsItem *> items = collidingItems(player);
    foreach(QGraphicsItem *item, items)
    {
        PropBox *propBox = qgraphicsitem_cast<PropBox *>(item);
        if(propBox)
        {
            if(player->isTouchingItemBottom(propBox))
            {
                //emit spawnCoin();

                controlPropBox(propBox);
                qDebug()<<"coin";
                if(propBox->propetyType == coinType)
                    coinInfo->increase(1);
                //qDebug()<<"collidingPropBOX";
            }
        }

    }
}

//与药剂碰撞
void GameScene::checkCollidingDrug()
{
    QList<QGraphicsItem *> items = collidingItems(player);
    foreach(QGraphicsItem *item, items)
    {
        Drug *drug = qgraphicsitem_cast<Drug *>(item);
        if(drug)
        {
            drugInfo->increase(1);
            removeItem(drug);

            removeItem(player);
            qDebug()<<"this is drug";
            qreal x = player->pos().x();
            qreal y = player->pos().y();
            int playerDirection = player->playerDirection;
            int playerStandingDirection = player->playerStandingDirection;
            if(drug->drugsType == speedDrugType)
            {
                player = new SpeedPlayer();
                if(playerDirection == 1)
                    player->addDirection(1);
                else if(playerDirection == -1)
                    player->addDirection(-1);
                else if(playerDirection == 0)
                {
                    //x = drug->pos().x() + drug->boundingRect().width() - player->boundingRect().width();
                    y = drug->pos().y() + drug->boundingRect().height() - player->boundingRect().height();
                }

                if(playerStandingDirection == 1)
                    player->addStandingDirection(1);
                else if(playerStandingDirection == -1)
                {
                    player->addStandingDirection(-1);
                    player->setTransform(QTransform(-1, 0, 0, 1, player->boundingRect().width(), 0));
                }

                velocity = 13;
                changeTimer->start(3000);
            }
            else if(drug->drugsType == jumpDrugType)
            {
                player = new JumpPlayer();
                if(playerDirection == 1)
                    player->addDirection(1);
                else if(playerDirection == -1)
                    player->addDirection(-1);
                else if(playerDirection == 0)
                {
                    //x = drug->pos().x() + drug->boundingRect().width() - player->boundingRect().width();
                    y = drug->pos().y() + drug->boundingRect().height() - player->boundingRect().height();
                }

                if(playerStandingDirection == 1)
                    player->addStandingDirection(1);
                else if(playerStandingDirection == -1)
                {
                    player->addStandingDirection(-1);
                    player->setTransform(QTransform(-1, 0, 0, 1, player->boundingRect().width(), 0));
                }

                jumpHeight = 300;
                jumpAnimation->stop();
                fallTimer.stop();
                player->walk();
                changeTimer->start(3000);
            }
            else if(drug->drugsType == growDrugType)
            {
                player = new GrowPlayer();
                if(playerDirection == 1)
                    player->addDirection(1);
                else if(playerDirection == -1)
                    player->addDirection(-1);
                else if(playerDirection == 0)
                {
                    //x = drug->pos().x() + drug->boundingRect().width() - player->boundingRect().width();
                    y = drug->pos().y() + drug->boundingRect().height() - player->boundingRect().height();
                }

                if(playerStandingDirection == 1)
                    player->addStandingDirection(1);
                else if(playerStandingDirection == -1)
                {
                    player->addStandingDirection(-1);
                    player->setTransform(QTransform(-1, 0, 0, 1, player->boundingRect().width(), 0));
                }

                damageInfo->increase(3);
                changeTimer->start(3000);
            }
            else if(drug->drugsType == recoverDrugType)
            {
                bloodInfo->increase(10);
            }


            player->setPos(x,y);
            addItem(player);

        }
    }
}


//与弹簧碰撞
void GameScene::checkCollidingSpring()
{
    QList<QGraphicsItem *> items = collidingItems(player);
    foreach(QGraphicsItem *item, items)
    {
        Spring *spring = qgraphicsitem_cast<Spring *>(item);
        if(spring)
        {
//            if(player->isTouchingBody(spring))
//            {
//                if(player->pos().x() < spring->pos().x())
//                    player->setPos(spring->pos().x() - player->boundingRect().width(), player->pos().y());
//                if(player->pos().x() > spring->pos().x())
//                    player->setPos(spring->pos().x() + spring->boundingRect().width(), player->pos().y());
//            }

            if(player->isTouchingItemUpper(spring))
            {
                qDebug()<<"collidingSpring";
                jumpHeight = 300;
                touchedSpring = true;
                return;

//                player->setPos(player->pos().x(), spring->pos().y() - player->boundingRect().height());
//                fallTimer.stop();
//                player->walk();
                //fallSpeed *= 2;
//    jumpAnimation->setDuration(800);
                //if(jumpAnimation->state() == QAbstractAnimation::Stopped)
//                {
                    //fallTimer.stop();
                    //jumpAnimation->start();
//                }
//                jumpHeight /= 2;
            }
            if(player->pos().x() + player->boundingRect().width() >= spring->pos().x()
                    && player->pos().x() <= spring->pos().x() + spring->boundingRect().width()
                    && player->pos().y() + player->boundingRect().height() >= spring->pos().y()
                    && player->pos().y() <= spring->pos().y() + spring->boundingRect().height())
            {
                if(player->pos().x() < spring->pos().x())
                    player->setPos(spring->pos().x()-player->boundingRect().width(),player->pos().y());
                else
                    player->setPos(spring->pos().x()+spring->boundingRect().width(),player->pos().y());
                touchedSpringButton = true;
//                qDebug()<<touchedSpringButton;
            }

        }
    }
//    if(player->pos().x() + player->boundingRect().width() < spring1->pos().x()
//            || player->pos().x() > spring1->pos().x() + spring1->boundingRect().width()
//            || player->pos().y() + player->boundingRect().height() < spring1->pos().y()
//            || player->pos().y() > spring1->pos().y() + spring1->boundingRect().height())
//    {
//        touchedSpringButton = false;
////        qDebug()<<touchedSpringButton;
//    }
}

void GameScene::checkCollidingChallengeDoor()
{
    if(player->pos().x() + player->boundingRect().width() >= challengeDoor1->pos().x()
    && player->pos().x() <= challengeDoor1->pos().x() + challengeDoor1->boundingRect().width()
    && player->pos().y() + player->boundingRect().height() >= challengeDoor1->pos().y()
    && player->pos().y() <= challengeDoor1->pos().y() + challengeDoor1->boundingRect().height())
    {
        challengeDoor1->setPixmap(QPixmap(":/src/images/enterChallenge.png"));
        touchedChallengeDoor = true;
//            player->stand();
        qDebug()<<"collidingDoor";
    }

//    QList<QGraphicsItem *>items = collidingItems(player);
//    foreach (QGraphicsItem *item, items)
//    {
//        ChallengeDoor *challengeDoor = qgraphicsitem_cast<ChallengeDoor *>(item);
//        if(challengeDoor)
//        {
//            challengeDoor->pixmap = QPixmap(":/src/images/enterChallenge.png");
//            touchedChallengeDoor = true;
////            player->stand();
//            qDebug()<<"collidingDoor";
//        }
//    }
}

void GameScene::checkNotCollidingChallengeDoor()
{
    if(player->pos().x() + player->boundingRect().width() < challengeDoor1->pos().x()
    || player->pos().x() > challengeDoor1->pos().x() + challengeDoor1->boundingRect().width()
    || player->pos().y() + player->boundingRect().height() < challengeDoor1->pos().y()
    || player->pos().y() > challengeDoor1->pos().y() + challengeDoor1->boundingRect().height())

    {
        challengeDoor1->setPixmap(QPixmap(":/src/images/challengeDoor.png"));
//        challengeDoor1->pixmap = QPixmap(":/src/images/challengeDoor.png");
        touchedChallengeDoor = false;
    }
}


