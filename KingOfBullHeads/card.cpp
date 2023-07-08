#include "card.h"
#include <QDebug>
#include <QBitmap>
#include <QPropertyAnimation>
#include "MyPushButton.h"
MyCard::MyCard(QWidget* parent,int _number,int w,int h):QPushButton(parent),card_number(_number)
{
    this->setMouseTracking(true);  //启用鼠标跟踪功能
    if(_number%55==0) heads_num=7;
    else if(_number%11==0) heads_num=5;
    else if(_number%20==0) heads_num=3;
    else if(_number%5==0) heads_num=2;
    else heads_num=1;
    QString tmp_Path = QString::number(card_number);
    card_Path = ":/res/cards/cards/" + tmp_Path + ".png";
    setFixedSize(w,h);
}
void MyCard::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    QImage image(card_Path);
    painter.drawImage(rect(), image);
}
void MyCard::mousePressEvent(QMouseEvent *e)
{
    if(is_play)
    {
        return;
    }
    if(!is_clicked)
    {
        QSound::play(":/res/Res/points.wav");  //点牌声效
        move(x(), y()-30);  //点下去
        is_clicked = 1;
        QPushButton::mousePressEvent(e);  // 调用基类的 mousePressEvent 函数处理默认行为
    }
    else if(is_clicked)
    {
        QSound::play(":/res/Res/points.wav");  //点牌声效
        move(x(), y()+30);  //点下去
        is_clicked = 0;
        QPushButton::mousePressEvent(e);  // 调用基类的 mousePressEvent 函数处理默认行为
    }


   return QPushButton::mousePressEvent(e);
}

//void MyCard::mouseReleaseEvent(QMouseEvent *e)
//{
//    if(is_play) return;
//    QSound::play(":/res/Res/points.wav");  //点牌声效

//    move(x(), y()-1);  //点起来
//    move(x(), y()+8);  //点起来

//    return QPushButton::mouseReleaseEvent(e);
//}
MyCard::~MyCard(){}
