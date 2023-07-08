#include <QDebug>
#include "Guy4PlayModeChoose.h"
Guy4PlayModeChoose::Guy4PlayModeChoose(QWidget *parent):QWidget(parent)
{
    bgm = new QSound(":/res/Res/battelbgm.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放
    Easy = new MyPushButton(this, 0, ":/button/button02.png", ":/button/button02.png");
    Medium = new MyPushButton(this, 0, ":/button/button13.png", ":/button/button13.png");
    Hard = new MyPushButton(this, 0, ":/button/button05.png", ":/button/button05.png");
    Return = new MyPushButton(this, 0, ":/button/button00.png", ":/button/button00.png");
    MainMenu = new MyPushButton(this, 0, ":/button/button06.png", ":/button/button06.png");
    Easy->resize(300,100);
    Easy->move(200,900);
    Hard->resize(300,100);
    Hard->move(1100,900);
    Medium->resize(300,100);
    Medium->move(650,900);
    Return->resize(200,100);
    Return->move(1125,0);
    MainMenu->resize(200,100);
    MainMenu->move(1365,0);
    Easy->setStyleSheet("font-size: 40px");
    Medium->setStyleSheet("font-size: 40px");
    Hard->setStyleSheet("font-size: 40px");
    Return->setStyleSheet("font-size: 30px");
    MainMenu->setStyleSheet("font-size: 30px");

}
void Guy4PlayModeChoose::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/menu.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
