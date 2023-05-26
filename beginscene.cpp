#include "beginscene.h"
#include <QDebug>
BeginScene::BeginScene(QWidget *parent):QWidget(parent){
    bgm = new QSound(":/res/Res/battelbgm.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放
    start = new MyPushButton(this,"Start");
    setting = new MyPushButton(this,"Settings");
    rule = new MyPushButton(this,"Rule");
    start->resize(150,50);
    start->move(325,450);
    setting->resize(150,50);
    setting->move(100,450);
    rule->resize(150,50);
    rule->move(550,450);
    start->setStyleSheet("font-size: 30px");
    setting->setStyleSheet("font-size: 30px");
    rule->setStyleSheet("font-size: 30px");
    Quitgame = new MyPushButton(this,"退出游戏");
    Quitgame->resize(100,50);
    Quitgame->move(700,0);
    Quitgame->setStyleSheet("font-size: 20px");

    //this,true,":/res/Res/Icon.png",":/res/Res/victory.png"

    //begin2game->move(100, 100);
    /*connect(begin2game, &MyPushButton::clicked, [=](){
        bgm->stop();
        emit Begin2Game();
    });*/
}

void BeginScene::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/Icon.ico");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}

