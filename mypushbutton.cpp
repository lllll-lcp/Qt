#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
MypushButton::MypushButton(QWidget *parent)
    : QPushButton{parent}
{}
MypushButton:: MypushButton(QString  normalImg,QString pressImg)
{
    this->normalImg=normalImg;
    this->pressImg=pressImg;

    QPixmap pix;
   bool ret= pix.load(normalImg);
    if(!ret)
   {
       qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));


}




void MypushButton::zoom1()//向下跳
{
    //创建动画对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geoetry");
    //设置动画事件间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束数位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}
void MypushButton::zoom2()//向上跳
{

    //创建动画对象
    QPropertyAnimation* animation=new QPropertyAnimation(this,"geometry");
    //设置动画事件间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束数位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}

 void MypushButton::mousePressEvent(QMouseEvent*e)
{
     if(this->pressImg !="")//传入的按下图片不为空 说明需要有按下的状态，切换图片
    {
        QPixmap pix;
        bool ret= pix.load(this->pressImg);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

     }
     //让父类执行其他内容
     return QPushButton::mousePressEvent(e);

}
void MypushButton::mouseReleaseEvent(QMouseEvent*e)
{

    if(this->pressImg !="")//传入的按下图片不为空 说明需要有按下的状态，切换初始图片
    {
        QPixmap pix;
        bool ret= pix.load(this->normalImg);
        if(!ret)
        {
            qDebug()<<"图片加载失败";
            return;
        }
        //设置图片固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));

    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);


}





