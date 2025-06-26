#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QDebug>
#include<QSoundEffect>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置选择关卡场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡场景");

    //创建菜单界面
    QMenuBar*bar=menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu*startMenu = bar->addMenu("开始");
    //创建退出的 菜单项
    QAction*quitAction=startMenu->addAction("退出");
    //点击退出
    connect(quitAction,&QAction::triggered,[this](){
        this->close();
    });

    //选择关卡按钮的音效
    QSoundEffect*chooseSOund=new QSoundEffect(this);
   chooseSOund->setSource(QUrl::fromLocalFile(":/BackButtonSound.wav"));

   //返回按钮音效
   QSoundEffect*backSound=new QSoundEffect(this);
  backSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));




    //返回按钮
    MypushButton*backBtn=new MypushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());


    //点击返回
    connect(backBtn,&MypushButton::clicked,[=](){
        //qDebug()<<"点击返回按钮";
        //告诉主场景 我返回了，主场景监听ChooseLevelScene的返回按钮
        //播放返回按钮音效
         backSound->play();

        QTimer::singleShot(500,this,[this](){
            emit this->chooseSceneBack();

        });


            });

    //创建选择关卡按钮
    for(int i=0;i<20;i++)
    {
        MypushButton*menuBtn=new MypushButton(":/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);

        //监听每个按钮的点击事件
        connect(menuBtn,&MypushButton::clicked,[=](){
            //播放选择关卡的音效
            chooseSOund->play();


            QString str=QString("您选择得是第 %1 关").arg(i+1);
            qDebug()<<str;

            //进入到游戏场景
            this->hide();
            play=new playScene(i+1);
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());

            play->show();

            connect(play,&playScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });
        });


        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        //设置label上的文字对齐 设置时评居中和设置垂直居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透   51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }



}
 void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    //加载背景
     QPainter  painter(this);
    QPixmap pix;
     pix.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //加载标题
    pix.load(":/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}





