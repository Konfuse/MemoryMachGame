#include "myScence.h"
#include <QPixmap>
#include <QSize>
#include <QDebug>
#include <QStack>
#include <synchapi.h>
myitem::myitem()
{
    QPixmap pic;
    pic.load(":/new/prefix1/Block.png");
    QSize picSize(25,25); //修改成25*25的图
    QPixmap tmpPic = pic.scaled(picSize);
    this->setPixmap(tmpPic);
    //为每个方框进行初始化
    flag = false;
    got_a_pair=false;
}


void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(this->flag == true||this->the_scence->cooldown==1) return ; //如果没有出现延迟情况 则跳过已经被翻过的被点击的牌 如果出现了 则全部锁定 无法选中
    qDebug()<<1;
    ;
    QSize pic(25,25);
    QString path = ":/new/prefix1/";
    QString fn ;
    int cutline;
    if(this->the_scence->typeButton == 1)
       fn = "ChineseNumber/",cutline=0;
    else if(this->the_scence->typeButton == 3)
        fn = "elements/",cutline=30;
    else
        fn = "pet/",cutline=100;
    path.append(fn);

    QString filname = QString::number(data,10);//每一个item类对应的data文件名
    QString fileType = data<cutline?".jpg":".png"; //检查后缀名 防止打开失败
    path.append(filname);
    path.append(fileType);

 //   QPixmap beforPic(final);
    QPixmap nPic(path); //变换之后的图
    qDebug()<<path;
    this->setPixmap(nPic.scaled(pic)); //进行图片的缩放和改变


    if(this->the_scence->tempitemA==NULL){ //存第一张
        this->the_scence->tempitemA=this;
        return ;
    }

        this->the_scence->tempitemB=this;
        //this->the_scence->cooldown = 1;
        got_a_pair = true;

}

void myitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){


    if(this->the_scence->cooldown==1 ) return ;
    if(this->flag == true&&this->the_scence->cooldown==0) return ;
    this->flag = true;
/*    QSize pic(25,25);
    QPixmap beforPic(":/new/prefix1/Block.png");

 //   this->setPixmap(nPic.scaled(pic)); //进行图片的缩放和改变
    if(fuckoff){
        this->the_scence->cooldown=1;
        this->the_scence->tme->start(this->the_scence->delay*1000);
        while(this->the_scence     ->cooldown);
        temp->setPixmap(beforPic.scaled(pic));
        this->setPixmap(beforPic.scaled(pic));
        this->the_scence->tmpitem=NULL;
    }*/
    if(got_a_pair)
    {

        this->the_scence->cooldown=1;   //进入只   看翻的牌啥都不干的挂机模式
        bool judge=false;
        if(this->the_scence->tempitemA->data == this->the_scence->tempitemB->data){
            judge=true;
            qDebug()<<"same";
            this->the_scence->tempitemA->flag=true;
            this->the_scence->tempitemB->flag=true;
            this->the_scence->tempitemA = this->the_scence->tempitemB=NULL;
            this->the_scence->cooldown=0;
            got_a_pair=false;

            return ;
        }

        if(!judge){
            this->the_scence->tme->start(this->the_scence->delay*1000);   //挂机x秒
            qDebug()<<this->the_scence->delay;

            got_a_pair=false;


        }

      //  this->the_scence->cooldown=0;
    }
}

