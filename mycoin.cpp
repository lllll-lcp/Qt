#include "mycoin.h"
#include<QDebug>
#include<QTimer>
// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {}
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
   bool ret= pix.load(btnImg);
    if(!ret)
   {
       QString str=QString("图片 %1 加载失败").arg(btnImg);
       qDebug()<<str;
       return ;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听正面翻反面得信号 并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断如果翻完了，将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;//停止做动画
            timer1->stop();
        }
    });




}
void  MyCoin::mousePreseEvent(QMouseEvent*e)
{
    if(this->isAnimation || this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}







//改变正反面
 void MyCoin::changeFlog()
{
    //如果是正面翻成反面
     if(this->flog)
    {
         //开始正面开反面得定时器
         timer1->start(30);
         isAnimation=true;//开始做动画
        this->flog=false;
     }
     else//反面翻正面
     {
         timer2->start(30);
         isAnimation=true;//开始做动画
         this->flog=true;
     }

     //监听反面翻正面得信号 并且反转金币
     connect(timer2,&QTimer::timeout,[=](){
         QPixmap pix;
         QString str=QString(":/Coin000%1.png").arg(this->max--);
         pix.load(str);

         this->setFixedSize(pix.width(),pix.height());
         this->setStyleSheet("QPushButton{border:0px;}");
         this->setIcon(pix);
         this->setIconSize(QSize(pix.width(),pix.height()));
         //判断如果翻完了，将min重置为1
         if(this->max<this->min)
         {
             this->max=8;
             isAnimation=false;//停止做动画
             timer2->stop();
         }
     });




}
