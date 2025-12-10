#ifndef BOMB_H
#define BOMB_H
#include"config.h"
#include<QPixmap>
#include<QVector>
  class Bomb{
    public:
    Bomb();
    //更新信息
    void updateInFo();
    public:
    //爆炸图片数组
    QVector<QPixmap> m_bombPixs;
    //位置
    int m_bomb_posX;
    int m_bomb_posY;
    //状态
    bool mb_isFree;
    //时间间隔
    int m_bomb_Recorder;
    //记录播放的图片下标
    int m_bomb_index;
  };
#endif // BOMB_H