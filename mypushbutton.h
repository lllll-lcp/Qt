#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MypushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MypushButton(QWidget *parent = nullptr);

    //构造函数  参数1 正常显示的图片  参数2 按下后的图片路径
    MypushButton(QString  normalImg,QString pressImg="");
    //成员属性 保存用户传入的默认显示路径 以及按下后的图片路径
    QString normalImg;
    QString pressImg;


    //弹跳特效
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写按钮 按下 和 释放事件
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
};

#endif // MYPUSHBUTTON_H
