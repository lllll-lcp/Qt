#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<QSoundEffect>
#include<QUrl>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置固定大小
    setFixedSize(320,588);
    //设置应用图片
   setWindowIcon(QIcon(":/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //实现退出
    connect( ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSoundEffect*startSOund=new QSoundEffect(this);
   startSOund->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));




    //开始按钮
    MypushButton *startBtn=new MypushButton(":/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //实例化选择关卡场景
    chooseScene=new ChooseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[this](){
        this->setGeometry( chooseScene->geometry());
        chooseScene->hide();//将选择的关卡场景 隐藏掉
        this->show();//重新显示主场景
    });


    connect(startBtn,&MypushButton::clicked,[=](){
       // qDebug()<<"点击开始·";
        //播放开始音效资源

           startSOund->play();


        //做一个弹起特效
        startBtn->zoom1();
        startBtn->zoom2();


        //延时进入进入选择关卡场景
        QTimer::singleShot(500,this,[=](){
            //设置 chooseScene场景位置
            chooseScene->setGeometry(this->geometry());
        //将自身隐藏
        this->hide();
        //显示选择关卡场景
        chooseScene->show();

         });

});
}
//设置绘图事件
void MainScene::paintEvent(QPaintEvent *)
{
//画家类
    QPainter painter(this);
     QPixmap pix;
    pix.load(":/PlayLevelSceneBg.png");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //背景上的图标
     pix.load(":/Title.png");
     //缩放图标
     pix.scaled(pix.width()*0.5,pix.height()*0.5);
     painter.drawPixmap(10,30,pix);



}


MainScene::~MainScene()
{
    delete ui;
}
