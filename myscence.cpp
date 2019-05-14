#include "myScence.h"
#include <QDebug>
#include <myitem.h>
#include <QVector>
#include <QPixmap>
#include <QGraphicsScene>
#include <time.h>
const int Filenum = 32;


myScence::myScence(QGraphicsScene *parent,int h,int t) : QGraphicsScene(parent)
{
    srand(time(NULL));
    //在构造函数中初始化主场景
    for(int i=0;i<h;i++){
        for(int j=0;j<h;j++){
            this->items[i][j] = new myitem();
            this->items[i][j]->x = i;
            this->items[i][j]->y = j;
            this->items[i][j]->the_scence = this;//--
            this->items[i][j]->flag=false;
            this->items[i][j]->setPos(0+ j*25,0 + i*25); //设置他们在主场景中的位置 但是不为它们分配图片
            this->addItem(this->items[i][j]); //加入到场景当中
        }
    }
    this->typeButton =0;
    this->delay = t;
    this->cooldown = 0;
    connect(tme, SIGNAL(timeout()), this, SLOT(update_cooldown()));
    //随机生成 路径对应到item[i][j]
    QVector<int> vec;
    bool number[100];
    memset(number,0,sizeof(number));
    for(int i=0;i<h*h/2;i++)
    {
        int index = rand()%Filenum+1;
        if(number[index] ==false)
        {
            number[index]=true;
            vec.push_back(index);
            qDebug()<<index;
        }
        else --i;
    }
    bool vis[200];
    int m = 0;
    memset(vis,0,sizeof(vis));
    QString path = ":/new/prefix1/";
    QString filType = ".png";
    for(int i=0;i<h*h/2;++i){
        int pos = rand()%(h*h);
        if(vis[pos]==false){
            vis[pos]=true;
            this->items[pos/h][pos%h]->data = vec[m];
            m++;
        }
        else --i;
    }
    m = 0;
    for(int i=0;i<h*h/2;++i){
        int pos = rand()%(h*h);
        if(vis[pos]==false){
            vis[pos]=true;
            this->items[pos/h][pos%h]->data = vec[m++];
            this->items[pos/h][pos%h]->flag = false;
        }
        else --i;
    }
}

void myScence::update_cooldown()
{

    this->cooldown=1;
    QSize pic(25,25);
    QPixmap beforPic(":/new/prefix1/Block.png");
  //  if(this->tempitemA->flag==false)
        this->tempitemA->setPixmap(beforPic.scaled(pic));
//    if(this->tempitemB->flag==false)
        this->tempitemB->setPixmap(beforPic.scaled(pic));
  //  this->tempitemA=this->tempitemB=NULL;
        this->tempitemA->flag = this->tempitemB->flag=false;
        this->tempitemA=this->tempitemB=NULL;

    this->tme->stop();
    this->cooldown = 0;

}
