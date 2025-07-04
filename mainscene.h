#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include<chooselevelscene.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainScene;
}
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    //重写piantEngine事件画背景图
    void paintEvent(QPaintEvent *);

    ChooseLevelScene * chooseScene=NULL;



private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
