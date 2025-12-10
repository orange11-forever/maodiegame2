#ifndef MAODIEPLANE_H
#define MAODIEPLANE_H
#include<QPixmap>
#include<QRECT>
#include"bullet.h"
class MAODIEPLANE
{
public:
    MAODIEPLANE();
    //子弹
    void shoot();
    //耄耋战机位置
    void setPosition(int x,int y);
public:
    QPixmap m_Plane;
    //坐标
    int m_X;
    int m_Y;
    //耄耋矩形边框
    QRect m_Rect;
    //弹匣
    Bullet m_bullets[BULLET_NUM];
    //发射间隔记录
    int m_Recorder=0;

};

#endif // MAODIEPLANE_H
