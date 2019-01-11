#ifndef TETRIS_H
#define TETRIS_H

#include "mainwindow.h"

const int BLOCK_SIZE=20; //单个方块单元的边长
const int MARGIN=5; //场景边距
const int AREA_ROW=23; //场景行数
const int AREA_COL=12; //场景列数
const int updatetime=20; //界面刷新速度

//方向
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE
};

//坐标
struct block_point
{
    int pos_x;
    int pos_y;
};

//namespace Ui {
//class Widget;
//}

class Tetris : public QWidget
{
    Q_OBJECT

public:
    void InitGame(); //初始化
    void StartGame(); //开始游戏
    void GameOver(); //游戏结束

    void ResetBlock(); //调取下一个方块
    void BlockMove(Direction dir); //方块移动
    void BlockRotate(int block[4][4]); //方块旋转
    void CreateBlock(int block[4][4],int block_id); //产生方块
    bool CollideCheck(int x,int y,Direction dir); //碰撞检测
    bool BoundCheck(int x,int y,Direction dir); //边界检测
    bool TransBoundary(int x,int y); //越界检测
    void RemoveBlock(int x,int y); //移除方块
    void ReturnBlock(int x,int y); //返还方块
    void EraseCheck(); //消行检测
    void DeadCheck(); //死亡检测
    void PauseGame(); //暂停/恢复游戏
    void LevelCheck();

public:
    explicit Tetris(QWidget *parent = 0);
    ~Tetris();

    virtual void paintEvent(QPaintEvent *event); //场景刷新
    virtual void keyPressEvent(QKeyEvent *event); //键盘响应

private:
    //Ui::Widget *ui;

private:
    int game_area[AREA_ROW][AREA_COL]; //场景区域，0表示空
    block_point blockpos; //当前方块坐标
    int cur_block[4][4]; //当前方块形状
    int next_block[4][4]; //下一个方块形状
    int score;  //游戏分数
    int paused;
    int downtime;
    int level;
    int times;
    QTimer *Downtime;
    QTimer *Updatetime;

private slots:
    void TimingDown();
};
#endif // TETRIS_H
