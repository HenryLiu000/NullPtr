#include <QDebug>
#include "choosemode.h"
ChooseModeScene::ChooseModeScene(QWidget *parent):QWidget(parent)
{
    bgm = new QSound(":/res/Res/bgm01.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放
    Guy2 = new MyPushButton(this, 0, ":/button/button09.png", ":/button/button09.png");
    Guy4 = new MyPushButton(this, 0, ":/button/button08.png", ":/button/button08.png");
    Quit = new MyPushButton(this, 0, ":/button/button01.png", ":/button/button01.png");
    Guy2->resize(300,100);
    Guy2->move(200,900);
    Guy4->resize(300,100);
    Guy4->move(1100,900);
    Quit->resize(300,100);
    Quit->move(650,900);
    Guy2->setStyleSheet("font-size: 40px");
    Guy4->setStyleSheet("font-size: 40px");
    Quit->setStyleSheet("font-size: 40px");
}
void ChooseModeScene::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/menu.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
ChooseModeScene::~ChooseModeScene()
{
    delete bgm;
    delete Guy2;
    delete Guy4;
    delete Quit;
}
