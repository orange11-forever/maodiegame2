#include "maodieplane.h"
#include"config.h"
MAODIEPLANE::MAODIEPLANE() {
//加载飞机图片资源
    m_Plane.load(maodie_PATH);
//耄耋飞机坐标
    m_X=(GAME_WIDTH-m_Plane.width())*0.5;
    m_Y=GAME_HEIGHT-m_Plane.height();
 //边框
    m_Rect.setWidth(m_Plane.width());
    m_Rect.setHeight(m_Plane.height());
    m_Rect.moveTo(m_X,m_Y);
}
void MAODIEPLANE::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}
void MAODIEPLANE::shoot(){

    //累加时间间隔

    m_Recorder++;
    if (m_Recorder<BULLET_INTERVAL){
        return;
    }
    
        m_Recorder=0;
        //发射
        for(int i=0;i<BULLET_NUM;i++){
            if(m_bullets[i].m_Free){
                m_bullets[i].m_Free=false;
                m_bullets[i].m_X=m_X+m_Rect.width()*0.5 -10;
                m_bullets[i].m_Y=m_Y-25;
                break;
            }
    }


}
