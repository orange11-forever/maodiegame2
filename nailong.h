#ifndef NAILONG_H
#define NAILONG_H  
#include<QPixmap>
class Nailong
{
  public:
  Nailong();
  //更新龙的坐标
  void updatePosition();
    public:
    //图片对象
    QPixmap m_nailong;
    //位置
    int m_nailong_posX;
    int m_nailong_posY;
   //矩形边框
   QRect m_nailong_Rect;
   //状态
    bool m_isFree;
    //速度
    int m_nailong_speed;
};
#endif // NAILONG_H