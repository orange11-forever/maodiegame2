#ifndef MAINSCENE_H
#define MAINSCENE_H
#include<QTimer>
#include <QWidget>
#include"map.h"
#include"maodieplane.h"
#include"bullet.h"
#include"nailong.h"
#include"config.h"
#include"bomb.h"
class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    //初始化场景
    void initScene();
    //启动游戏
    void playGame();
    //更新元素坐标
    void updatePosition();
    //绘制到屏幕
    void paintEvent(QPaintEvent*);
    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent*);
    //奶龙来袭
    void nailongToScene();
    //碰撞检测
    void collisionDetection();
    //奶龙组
    Nailong m_nailongs[NAILONG_NUM];
    //时间间隔
    int m_nailong_recorder;
    //地图对象
    Map m_map;
    //定时器
    QTimer m_Timer;
    //飞机对象
    MAODIEPLANE m_maodie;
    //子弹
   Bullet m_bullets[BULLET_NUM];
   //子弹发射间隔记录
   int m_recorder;
   //爆炸数组
    Bomb m_bombs[BOMB_NUM];
};
#endif // MAINSCENE_H
