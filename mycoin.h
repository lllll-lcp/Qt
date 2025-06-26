#ifndef MYCOIN_H
#define MYCOIN_H

#include "qtimer.h"
#include <QpushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //参数代表 传入金币路径 还是银币路径
    MyCoin(QString btnImg);


    //金币得属性
    int posX;//X坐标
    int posY;//Y坐标
    bool flog;//正反标志

    void changeFlog();//改变标志
    QTimer *timer1;//正面翻反面 定时器
    QTimer *timer2;//反面翻正面 定时器
    int min=1;//最大图片
    int max=8;//最小图片

    //执行动画的标志
    bool isAnimation=false;
    //重写 按下和释放
    void mousePreseEvent(QMouseEvent*e);

   //是否胜利的标志
    bool isWin=false;



signals:
};

#endif // MYCOIN_H
