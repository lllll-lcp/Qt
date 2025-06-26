#include "playscene.h"
#include "qmenu.h"
#include "qmenubar.h"
#include "qtimer.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QString>
#include<mycoin.h>
#include<datacoin.h>
#include<QPropertyAnimation>
#include<QSoundEffect>
// playScene::playScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
playScene::playScene(int levelNum)
{
    QString str=QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/Coin0001.png"));
    //设置标题
    this->setWindowTitle("游戏场景");
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

    //返回按钮音效
    QSoundEffect*backSound=new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/TapButtonSound.wav"));

    //翻金币按钮音效
    QSoundEffect*flipSound=new QSoundEffect(this);
    flipSound->setSource(QUrl::fromLocalFile(":/ConFlipSound.wav"));
    //胜利按钮音效
    QSoundEffect*winSound=new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/LevelWinSound.wav"));

    //返回按钮
    MypushButton*backBtn=new MypushButton(":/BackButton.png",":/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());


    //点击返回
    connect(backBtn,&MypushButton::clicked,[=](){
        qDebug()<<"翻金币场景中点击返回按钮";
        //播放返回按钮的音效
        backSound->play();

        QTimer::singleShot(500,this,[this](){
            emit this->chooseSceneBack();

       });


    });
    //显示当前关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1=QString ("Levev:%1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);


    dataCoin coin;
    //初始化每个关卡得二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=coin.mData[this->levelIndex][i][j];
        }
    }

    //胜利图片显示
    QLabel*winLabel=new QLabel;
    QPixmap tmpix;
    tmpix.load(":/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpix.width(),tmpix.height());
    winLabel->setPixmap(tmpix);
    winLabel->setParent(this);
    winLabel->move((this->width() -tmpix.width())*0.5,-tmpix.height());


    //显示金币得背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            QPixmap pix= QPixmap(":/BoardNode.png");
            QLabel *label=new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,200+j*50);


            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str=":/Coin0001.png";
            }
            else
            {
                str=":/Coin0008.png";
            }
            MyCoin*coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flog=this->gameArray[i][j];//1正面 0反面
            //将金币放入到金币的二维数组里 以便于后期维护
            coinBtn[i][j]=coin;



            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                flipSound->play();
                //点击按钮 将所有按钮先禁用
                for(int i=0;i<4;i++)
                    {
                    for(int j=0;j<4;j++)
                    {
                        this->coinBtn[i][j]->isWin=true;
                    }
                }
                coin->changeFlog();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                //翻转周围金币
                //周围的右侧金币翻转条件,延时翻转
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlog();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;

                    }
                    //周围的左侧硬币翻转条件
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlog();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }

                    //周围上侧的硬币翻转
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlog();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    //周围下侧的硬币翻转
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlog();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    //判断是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++)
                    {


                        for(int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flog==false)//只要有一个是反面那就是失败
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                        //添加胜利音效
                        winSound->play();
                        //胜利了
                        qDebug()<<"游戏胜利";
                        //将所有按钮的胜利标志改为true,如果再次点击直接return 掉，不做响应
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        //将胜利的图片移动下来
                        QPropertyAnimation* animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        //设置曲线
                            animation->setEasingCurve(QEasingCurve::OutBounce );
                        //执行动画
                        animation->start();
                    }


                });
            });
        }
    }
}
   void playScene::paintEvent(QPaintEvent*)
{

    //创建背景
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
