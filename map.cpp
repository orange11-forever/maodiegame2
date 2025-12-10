#include "map.h"
#include"config.h"
Map::Map() {
    //初始化加载地图对象
    m_map1.load(":/new/prefix1/image/4C50EE5C4887E5789CE5A8B058B41888.jpg");
    m_map2.load(":/new/prefix1/image/4C50EE5C4887E5789CE5A8B058B41888.jpg");
    //Y轴坐标
    m_map1_posY=-GAME_HEIGHT;
    m_map2_posY=0;
    //滚动速度
    m_scroll_speed=MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{//处理第一张位置
    m_map1_posY+=m_scroll_speed;
    if(m_map1_posY>=0){
        m_map1_posY=-GAME_HEIGHT;
    }
    //第二张位置
    m_map2_posY+=m_scroll_speed;
    if(m_map2_posY>=GAME_HEIGHT){
        m_map2_posY=0;
    }
}
