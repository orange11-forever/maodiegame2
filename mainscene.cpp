#include "mainscene.h"
#include"config.h"
#include<QPainter>
#include<QMouseEvent>
#include<QtMultimedia/QSoundEffect>
#include<QUrl>
#include<ctime>
MainScene::MainScene(QWidget *parent)
 : QWidget(parent)
{
    
    //调用初始化场景
    initScene();
    //启动
    playGame();
}
MainScene::~MainScene()
{

}
void MainScene::initScene(){
    //设置固定尺寸
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置标题
    setWindowTitle(GAME_TITLE);
    //加载图标
    setWindowIcon(QIcon(":/new/prefix1/image/172555e58d9f3681480740715a6cad36.jpg"));
    //定时器
    m_Timer.setInterval(GAME_RATE);
    //奶龙时间间隔初始化
    m_nailong_recorder=0;
    //随机数种子
    srand((unsigned int)time(NULL));
    
}
void MainScene::playGame()
{    //背景音乐
    QSoundEffect *sound1= new QSoundEffect(this);
    sound1->setSource(QUrl::fromLocalFile(SOUND_BACKGROUND));
    sound1->setLoopCount(QSoundEffect::Infinite);
    sound1->setVolume(0.5f);
    sound1->play();
    //启动定时器
    m_Timer.start();
    //监听定时器信号
    connect(&m_Timer,&QTimer::timeout,[=](){
        //奶龙来袭
        nailongToScene();
        //更新元素坐标并刷新绘制
        updatePosition();
        update();
        //碰撞检测
        collisionDetection();
    }

            );

}

void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    //子弹
    m_maodie.shoot();
    for(int i=0;i<BULLET_NUM;i++){
        if(m_maodie.m_bullets[i].m_Free==false)
        {
            m_maodie.m_bullets[i].updatePosition();
        }
    }
    //奶龙坐标更新
    for(int i=0;i<NAILONG_NUM;i++){
        if(m_nailongs[i].m_isFree==false){
            m_nailongs[i].updatePosition();
        }
    }
    //计算爆炸播放的图片
    for(int i=0;i<BOMB_NUM;i++){
        if(m_bombs[i].mb_isFree==false){
            m_bombs[i].updateInFo();
        }
    }
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);
    //绘制耄耋
    painter.drawPixmap(m_maodie.m_X,m_maodie.m_Y,m_maodie.m_Plane);
    //子弹绘制
    for(int i=0;i<BULLET_NUM;i++){
        if(m_maodie.m_bullets[i].m_Free==false){
            painter.drawPixmap(m_maodie.m_bullets[i].m_X,m_maodie.m_bullets[i].m_Y,m_maodie.m_bullets[i].m_Bullet);
        }
    }
    //奶龙绘制
    for(int i=0;i<NAILONG_NUM;i++){
        if(m_nailongs[i].m_isFree==false){
            painter.drawPixmap(m_nailongs[i].m_nailong_posX,m_nailongs[i].m_nailong_posY,m_nailongs[i].m_nailong);
        }
    }
    //爆炸绘制
    for(int i=0;i<BOMB_NUM;i++){
        if(m_bombs[i].mb_isFree==false){
            painter.drawPixmap(m_bombs[i].m_bomb_posX,m_bombs[i].m_bomb_posY,m_bombs[i].m_bombPixs[m_bombs[i].m_bomb_index]);
        }
    }
}

void MainScene::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos =event->position();
    int x = pos.x()-m_maodie.m_Rect.width()*0.5;
    int y = pos.y()-m_maodie.m_Rect.height()*0.5;
    //边界检测
    if(x<=0){
        x=0;
    }
    if(x>=GAME_WIDTH-m_maodie.m_Rect.width()){
        x=GAME_WIDTH-m_maodie.m_Rect.width();
    }
    if(y<=0){
        y=0;
    }
    if(y>=GAME_HEIGHT-m_maodie.m_Rect.height()){
        y=GAME_HEIGHT-m_maodie.m_Rect.height();
    }
    m_maodie.setPosition(x,y);
}
//奶龙来袭
void MainScene::nailongToScene(){
    //累加时间间隔
    m_nailong_recorder++;
    if(m_nailong_recorder<NAILONG_INTERVAL){
        return;
    }
    m_nailong_recorder=0;
    //奶龙出场
    for(int i=0;i<NAILONG_NUM;i++){
        //空闲状态奶龙出场
        if(m_nailongs[i].m_isFree==true){
            //改变状态
            m_nailongs[i].m_isFree=false;
            //奶龙位置
            m_nailongs[i].m_nailong_posX=rand()%(GAME_WIDTH - m_nailongs[i].m_nailong_Rect.width());
            m_nailongs[i].m_nailong_posY=-m_nailongs[i].m_nailong_Rect.height();
            //更新边框位置
            m_nailongs[i].m_nailong_Rect.moveTo(m_nailongs[i].m_nailong_posX,m_nailongs[i].m_nailong_posY);
            break;
        }
    }
}
//碰撞检测
void MainScene::collisionDetection(){
   //遍历所有非空闲奶龙
   for(int i=0;i<NAILONG_NUM;i++){
       if(m_nailongs[i].m_isFree){
              continue;
       }
         //遍历所有非空闲子弹
         for(int j=0;j<BULLET_NUM;j++){
              if(m_maodie.m_bullets[j].m_Free){
                continue;
              }
              //碰撞检测
              if(m_nailongs[i].m_nailong_Rect.intersects(m_maodie.m_bullets[j].m_Rect)){
                //奶龙和子弹都设为free
                m_nailongs[i].m_isFree=true;
                m_maodie.m_bullets[j].m_Free=true;
                //播放爆炸效果
                for(int k=0;k<BOMB_NUM;k++){ 
                    if(m_bombs[k].mb_isFree){
                        //播放音效
                        QSoundEffect *sound = new QSoundEffect(this);
                        sound->setSource(QUrl::fromLocalFile(SOUND_BOMB));
                        sound->setVolume(0.5f);
                        sound->play();
                        //改变状态
                        m_bombs[k].mb_isFree=false;
                        //位置
                        m_bombs[k].m_bomb_posX=m_nailongs[i].m_nailong_posX + m_nailongs[i].m_nailong_Rect.width()*0.5 - m_bombs[k].m_bombPixs[0].width()*0.5;
                        m_bombs[k].m_bomb_posY=m_nailongs[i].m_nailong_posY + m_nailongs[i].m_nailong_Rect.height()*0.5 - m_bombs[k].m_bombPixs[0].height()*0.5;
                        //退出循环
                        break;
                    }
                }
                break;
              }


       }
   }
         
}