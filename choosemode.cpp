#include <QDebug>
#include "choosemode.h"
ChooseModeScene::ChooseModeScene(QWidget *parent):QWidget(parent)
{
    bgm = new QSound(":/res/Res/battelbgm.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放
    Guy2 = new MyPushButton(this,"双人模式");
    Guy4 = new MyPushButton(this,"四人模式");
    Quit = new MyPushButton(this,"退出");
    Guy2->resize(150,50);
    Guy2->move(100,450);
    Guy4->resize(150,50);
    Guy4->move(550,450);
    Quit->resize(150,50);
    Quit->move(325,450);
    Guy2->setStyleSheet("font-size: 30px");
    Guy4->setStyleSheet("font-size: 30px");
    Quit->setStyleSheet("font-size: 30px");
}
void ChooseModeScene::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/Icon.ico");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
