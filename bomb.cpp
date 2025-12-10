#include"bomb.h"
#include"config.h"
Bomb::Bomb()
{
    //爆炸图片放入数组
    for(int i=0;i<BOMB_MAX;i++){
        QString str =QString(BOMB_PATH).arg(i);
       m_bombPixs.push_back(QPixmap(str));
    }
    //位置
    m_bomb_posX=0;
    m_bomb_posY=0;
    //状态
    mb_isFree=true;
    //时间间隔
    m_bomb_Recorder=0;
    //播放图片下标
    m_bomb_index=0;
}
void Bomb::updateInFo()
{
    if(mb_isFree){
        return;
    }
    //累加时间间隔,未到达不需要切图
    m_bomb_Recorder++;
    if(m_bomb_Recorder<BOMB_INTERVAL){
        return;
    }
    //切图
    m_bomb_Recorder=0;
    m_bomb_index++;
    if(m_bomb_index>BOMB_MAX-1){
        mb_isFree=true;
        m_bomb_index=0;
    }
}