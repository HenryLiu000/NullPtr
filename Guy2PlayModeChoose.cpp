#include <QDebug>
#include "Guy2PlayModeChoose.h"
Guy2PlayModeChoose::Guy2PlayModeChoose(QWidget *parent):QWidget(parent)
{
    bgm = new QSound(":/res/Res/battelbgm.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放
    Easy = new MyPushButton(this,"简单");
    Medium = new MyPushButton(this,"适中");
    Hard = new MyPushButton(this,"困难");
    Return = new MyPushButton(this,"返回");
    MainMenu = new MyPushButton(this,"主菜单");
    Easy->resize(150,50);
    Easy->move(100,450);
    Hard->resize(150,50);
    Hard->move(550,450);
    Medium->resize(150,50);
    Medium->move(325,450);
    Return->resize(100,50);
    Return->move(600,0);
    MainMenu->resize(100,50);
    MainMenu->move(700,0);
    Easy->setStyleSheet("font-size: 30px");
    Medium->setStyleSheet("font-size: 30px");
    Hard->setStyleSheet("font-size: 30px");
    Return->setStyleSheet("font-size: 20px");
    MainMenu->setStyleSheet("font-size: 20px");

}
void Guy2PlayModeChoose::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/Icon.ico");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
