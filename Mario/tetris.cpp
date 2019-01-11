#include "tetris.h"

//定义图案
//田
int shape1[4][4]=
{
    {0,0,0,0},
    {0,1,1,0},
    {0,1,1,0},
    {0,0,0,0}
};
//L
int shape2[4][4]=
{
    {0,2,0,0},
    {0,2,0,0},
    {0,2,2,0},
    {0,0,0,0}
};
//反L
int shape3[4][4]=
{
    {0,0,3,0},
    {0,0,3,0},
    {0,3,3,0},
    {0,0,0,0}
};
//Z
int shape4[4][4]=
{
    {0,0,0,0},
    {0,4,4,0},
    {0,0,4,4},
    {0,0,0,0}
};
//反Z
int shape5[4][4]=
{
    {0,0,0,0},
    {0,5,5,0},
    {5,5,0,0},
    {0,0,0,0}
};
//凸
int shape6[4][4]=
{
    {0,0,0,0},
    {0,0,6,0},
    {0,6,6,6},
    {0,0,0,0}
};
//I
int shape7[4][4]=
{
    {0,0,7,0},
    {0,0,7,0},
    {0,0,7,0},
    {0,0,7,0}
};

Tetris::Tetris(QWidget *parent) :
    QWidget(parent)
    //ui(new Ui::Widget)
{
    //ui->setupUi(this);
    setFixedSize(400,445);
    setMinimumSize(BLOCK_SIZE*(AREA_COL+6)+MARGIN*2,BLOCK_SIZE*AREA_ROW+MARGIN*2);  //窗口最小大小
//    setGeometry(0,0,400,445);
    setWindowTitle(tr("俄罗斯方块"));

    this->Downtime = new QTimer(this);
    connect(this->Downtime,SIGNAL(timeout()),this,SLOT(TimingDown()));
    this->Updatetime = new QTimer(this);
    connect(this->Updatetime,SIGNAL(timeout()),this,SLOT(update()));

    InitGame();  //初始化游戏
}

Tetris::~Tetris()
{
//    delete ui;
}

void Tetris::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  //绘制游戏场景边框及预告方块
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN+BLOCK_SIZE*3,AREA_COL*BLOCK_SIZE,AREA_ROW*BLOCK_SIZE-BLOCK_SIZE*3);
    painter.setBrush(QBrush(Qt::color0,Qt::SolidPattern));
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(next_block[i][j]!=0)
                painter.drawRect(MARGIN*3+AREA_COL*BLOCK_SIZE+j*BLOCK_SIZE,MARGIN+(i+3)*BLOCK_SIZE,BLOCK_SIZE,BLOCK_SIZE);

    painter.setPen(Qt::black);  //绘制其他显示信息
    painter.setFont(QFont("Arial",12));
    painter.drawText(QRect(MARGIN*2+AREA_COL*BLOCK_SIZE,MARGIN*2+6*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4)
                     ,Qt::AlignCenter,tr("得分： ")+QString::number(score));
    painter.drawText(QRect(MARGIN*2+AREA_COL*BLOCK_SIZE,MARGIN*2+8*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4)
                     ,Qt::AlignCenter,tr("等级： ")+QString::number(level));
    if(paused==1)
    {
        painter.setFont(QFont("Arial",16));
        painter.drawText(QRect(MARGIN*2+(AREA_COL/2-3)*BLOCK_SIZE,MARGIN,BLOCK_SIZE*6,BLOCK_SIZE*4)
                         ,Qt::AlignCenter,tr("游戏已暂停"));
    }

    for(int i=3;i<AREA_ROW;i++)   //绘制游戏池区域内方块
        for(int j=0;j<AREA_COL;j++)
        {
            if(game_area[i][j]==1)
            {
                painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==2)
            {
                painter.setBrush(QBrush(Qt::yellow,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==3)
            {
                painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==4)
            {
                painter.setBrush(QBrush(Qt::blue,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==5)
            {
                painter.setBrush(QBrush(Qt::cyan,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==6)
            {
                painter.setBrush(QBrush(Qt::darkMagenta,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
            if(game_area[i][j]==7)
            {
                painter.setBrush(QBrush(Qt::magenta,Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            }
        }
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    if(paused==0)  //判断游戏是否已暂停
    {
        switch(event->key())
        {
        case Qt::Key_Up:
            BlockMove(UP);
            break;
        case Qt::Key_Down:
            BlockMove(DOWN);
            break;
        case Qt::Key_Left:
            BlockMove(LEFT);
            break;
        case Qt::Key_Right:
            BlockMove(RIGHT);
            break;
        case Qt::Key_Space:
            BlockMove(SPACE);
            break;
        case Qt::Key_W:
            BlockMove(UP);
            break;
        case Qt::Key_S:
            BlockMove(DOWN);
            break;
        case Qt::Key_A:
            BlockMove(LEFT);
            break;
        case Qt::Key_D:
            BlockMove(RIGHT);
            break;
        case Qt::Key_0:
            PauseGame();
            break;
        case Qt::Key_F:
            PauseGame();
            break;
        default:
            break;
        }
    }
    else
    {
        switch(event->key())
        {
        case Qt::Key_0:
            PauseGame();
            break;
        case Qt::Key_F:
            PauseGame();
            break;
        default:
            break;
        }
    }

}

void blockcopy(int block1[4][4],int block2[4][4])
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            block1[i][j]=block2[i][j];
}

void Tetris::CreateBlock(int block[4][4],int block_id)
{
    switch (block_id)
    {
    case 0:
        blockcopy(block,shape1);
        break;
    case 1:
        blockcopy(block,shape2);
        break;
    case 2:
        blockcopy(block,shape3);
        break;
    case 3:
        blockcopy(block,shape4);
        break;
    case 4:
        blockcopy(block,shape5);
        break;
    case 5:
        blockcopy(block,shape6);
        break;
    case 6:
        blockcopy(block,shape7);
        break;
    default:
        break;
    }
}

void Tetris::InitGame()
{
    for(int i=0;i<AREA_ROW;i++)  //初始化游戏池区域
        for(int j=0;j<AREA_COL;j++)
            game_area[i][j]=0;

    srand(time(0));  //初始化随机数种子
    score=0;
    paused=0;
    downtime=600;

    StartGame();  //开始游戏
}

void Tetris::EraseCheck()  //消行检测，并且给予消行奖励分
{
    int i=AREA_ROW-1;
    int countline=0;
    while(i>0)
    {
        for(int j=0;j<AREA_COL;j++)
        {
            if(game_area[i][j]==0)
            {
                i--;
                break;
            }
            else if(j==AREA_COL-1)
            {
                countline++;
                for(int k=i;k>0;k--)
                    for(int j=0;j<AREA_COL;j++)
                        game_area[k][j]=game_area[k-1][j];
            }
        }
    }
    score+=countline*countline*10;  //计算得分
}

void Tetris::GameOver()  //游戏结束
{
    Downtime->stop();
    Updatetime->stop();
    int reply;
    //reply = QMessageBox::information(this, NULL, "Game Over", QMessageBox::Ok);
    this->close();

}

void Tetris::PauseGame()  //暂停/恢复游戏
{
    if(paused==0)
    {
        Downtime->stop();
        paused=1;
    }
    else
    {
        Downtime->start(downtime);
        paused=0;
    }
}

void Tetris::DeadCheck()  //死亡检测
{
    for(int i=0;i<4;i++)
    {
       for(int j=0;j<AREA_COL;j++)
           if(game_area[i][j]!=0)
               GameOver();
    }
}

void Tetris::LevelCheck()
{
    level=score/600;
    if(level>9)
        level=10;
    Downtime->start(downtime-40*level);
}

void Tetris::ResetBlock()
{
    EraseCheck();
    LevelCheck();

    blockcopy(cur_block,next_block);  //产生当前方块
    int block_id=rand()%7;            //产生下一个方块
    CreateBlock(next_block,block_id);

    //设置初始方块坐标,以方块左上角为锚点
    block_point start_point;
    start_point.pos_x=AREA_COL/2-2;
    start_point.pos_y=0;
    blockpos=start_point;
    DeadCheck();
}

void Tetris::StartGame()
{
    Downtime->start(downtime);
    Updatetime->start(updatetime);

    int block_id=rand()%7;  //产生初始下一个方块
    CreateBlock(next_block,block_id);
    ResetBlock(); //产生方块
}

void Tetris::BlockRotate(int block[4][4])    //顺时针旋转方块
{
    int temp_block[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            temp_block[i][j]=block[3-j][i];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            block[i][j]=temp_block[i][j];
}

bool Tetris::TransBoundary(int x,int y)   //越界检测
{
    int testblock[4][4]={0};
    int testarea[AREA_ROW][AREA_COL]={0};  //用testarea模拟game_area
    int cross=0;
    for(int i=0;i<4;i++)  //用testblock模拟cur_blcok
    {
        for(int j=0;j<4;j++)
        {
            if(cur_block[i][j]!=0)
                testblock[i][j]=1;
        }
    }
    BlockRotate(testblock);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(testblock[i][j]!=0)
                testarea[y+i][x+j]=testblock[i][j];
        }
    }
    for(int i=0;i<AREA_ROW;i++)
    {
        if(testarea[i][0]!=0)
        {
            cross+=1;
            break;
        }
    }
    for(int i=0;i<AREA_ROW;i++)
    {
        if(testarea[i][AREA_COL-1]!=0)
        {
            cross+=1;
            break;
        }
    }
    if(cross==2)
        return true;
    else
        return false;
}

bool Tetris::CollideCheck(int x,int y,Direction dir)  //碰撞检测
{
    int testblock[4][4]={0};
    int testarea[AREA_ROW][AREA_COL]={0};
    for(int i=0;i<4;i++)  //用testblock模拟cur_blcok
    {
        for(int j=0;j<4;j++)
        {
            if(cur_block[i][j]!=0)
                testblock[i][j]=1;
        }
    }
    for(int i=0;i<AREA_ROW;i++)  //用testarea模拟game_area
        for(int j=0;j<AREA_COL;j++)
        {
            testarea[i][j]=game_area[i][j];
        }
    for(int i=0;i<4;i++)  //从testarea中移除cur_block
    {
        for(int j=0;j<4;j++)
        {
            if(cur_block[i][j]!=0)
                testarea[y+i][x+j]=0;
        }
    }
    switch(dir)  //先尝试按照指令移动一次
    {
    case UP:
        BlockRotate(testblock);
        break;
    case DOWN:
        y+=1;
        break;
    case LEFT:
        x-=1;
        break;
    case RIGHT:
        x+=1;
        break;
    default:
        break;
    }

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(testarea[y+i][x+j]!=0 && testblock[i][j]!=0)
                return true;
    return false;
}

bool Tetris::BoundCheck(int x,int y,Direction dir)  //边界检测
{
    switch(dir)
    {
    case DOWN:
        for(int i=3;i>=0;i--)
        {
            for(int j=0;j<4;j++)
            {
                if(cur_block[i][j]!=0 && y==AREA_ROW-1-i)
                    return true;
            }
        }
        return false;
    case LEFT:
        for(int j=0;j<4;j++)
        {
            for(int i=0;i<4;i++)
            {
                if(cur_block[i][j]!=0 && x==-j)
                    return true;
            }
        }
        return false;
    case RIGHT:
        for(int j=3;j>=0;j--)
        {
            for(int i=0;i<4;i++)
            {
                if(cur_block[i][j]!=0 && x==AREA_COL-1-j)
                    return true;
            }
        }
        return false;
    default:
        break;
    }
}

void Tetris::RemoveBlock(int x,int y)  //移除当前方块
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(cur_block[i][j]!=0)
                game_area[y+i][x+j]=0;
        }
    }
}

void Tetris::ReturnBlock(int x,int y)  //返还当前方块
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(cur_block[i][j]!=0)
                game_area[y+i][x+j]=cur_block[i][j];
        }
    }
}

void Tetris::TimingDown()
{
    if(BoundCheck(blockpos.pos_x,blockpos.pos_y,DOWN))
    {
        ResetBlock();
        return;
    }
    if(CollideCheck(blockpos.pos_x,blockpos.pos_y,DOWN))
    {
        ResetBlock();
        return;
    }
    RemoveBlock(blockpos.pos_x,blockpos.pos_y);
    blockpos.pos_y+=1;
    ReturnBlock(blockpos.pos_x,blockpos.pos_y);
}

void Tetris::BlockMove(Direction dir)
{
    switch (dir) {
    case UP:
        if(CollideCheck(blockpos.pos_x,blockpos.pos_y,UP))
            break;
        if(TransBoundary(blockpos.pos_x,blockpos.pos_y))
            break;
        RemoveBlock(blockpos.pos_x,blockpos.pos_y);
        BlockRotate(cur_block);
        ReturnBlock(blockpos.pos_x,blockpos.pos_y);
        break;
    case DOWN:
        if(BoundCheck(blockpos.pos_x,blockpos.pos_y,DOWN))
        {
            ResetBlock();
            break;
        }
        if(CollideCheck(blockpos.pos_x,blockpos.pos_y,DOWN))
        {
            ResetBlock();
            break;
        }
        RemoveBlock(blockpos.pos_x,blockpos.pos_y);
        blockpos.pos_y+=1;
        ReturnBlock(blockpos.pos_x,blockpos.pos_y);
        break;
    case LEFT:
        if(BoundCheck(blockpos.pos_x,blockpos.pos_y,LEFT))
            break;
        if(CollideCheck(blockpos.pos_x,blockpos.pos_y,LEFT))
            break;
        RemoveBlock(blockpos.pos_x,blockpos.pos_y);
        blockpos.pos_x-=1;
        ReturnBlock(blockpos.pos_x,blockpos.pos_y);
        break;
    case RIGHT:
        if(BoundCheck(blockpos.pos_x,blockpos.pos_y,RIGHT))
            break;
        if(CollideCheck(blockpos.pos_x,blockpos.pos_y,RIGHT))
            break;
        RemoveBlock(blockpos.pos_x,blockpos.pos_y);
        blockpos.pos_x+=1;
        ReturnBlock(blockpos.pos_x,blockpos.pos_y);
        break;
    case SPACE: //沉底
        RemoveBlock(blockpos.pos_x,blockpos.pos_y);
        while(!CollideCheck(blockpos.pos_x,blockpos.pos_y,DOWN)&&!BoundCheck(blockpos.pos_x,blockpos.pos_y,DOWN))
        {
            blockpos.pos_y+=1;
        }
        ReturnBlock(blockpos.pos_x,blockpos.pos_y);
        ResetBlock();
        break;
    default:
        break;
    }
}
