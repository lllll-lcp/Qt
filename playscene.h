#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<mycoin.h>
class playScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScene(QWidget *parent = nullptr);
    playScene(int levelNum);
    int levelIndex;//内部得成员属性 记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent*);

    int gameArray[4][4];//二维数组 维护每个关卡得具体数据

    MyCoin*coinBtn[4][4];

    //是否胜利的标志
    bool isWin=true;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
