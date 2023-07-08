#include "MyPushButton.h"
#include<QDebug>
#include<QString>
#include<QPropertyAnimation>
#include<QBitmap>
#include<QSound>

MyPushButton::MyPushButton(QWidget* parent,bool mask,QString normalImg,QString pressedImg):QPushButton(parent),normalImgPath(normalImg),pressedImgPath(pressedImg){
    setCursor(Qt::PointingHandCursor);//设置鼠标形状
    QPixmap pix;
    bool ret=pix.load(normalImgPath);//加载图片
    if(normalImg==":/button/button04.png" || normalImg==":/button/button03.png" || normalImg==":/button/button12.png"){
        pix= pix.scaled(pix.size()*0.8);
    }
    else if(normalImg==":/button/button01.png" || normalImg==":/button/button08.png" || normalImg==":/button/button09.png"){
        pix= pix.scaled(pix.size()*0.8);
    }
    else if(normalImg==":/button/button02.png" || normalImg==":/button/button05.png" || normalImg==":/button/button13.png"){
        pix= pix.scaled(pix.size()*0.8);
    }
    else if(normalImg==":/button/button10.png"){
        pix= pix.scaled(pix.size()*0.6);
    }
    else if(normalImg==":/button/button00.png"){
        pix= pix.scaled(pix.size()*0.6);
    }
    else if(normalImg==":/button/button06.png"){
        pix= pix.scaled(pix.size()*0.6);
    }
    else if(normalImg==":/button/button11.png"){
        pix= pix.scaled(pix.size()*0.58);
    }
    else if(normalImg==":/button/button15.png" || normalImg==":/button/button16.png"){
        pix= pix.scaled(pix.size()*0.4);
    }
    else if(normalImg==":/res/Res/victoryPic.png" || normalImg==":/res/Res/losePic.png" || normalImg==":/res/Res/pingjuPic.png"){
        pix= pix.scaled(pix.size()*3.5);
    }
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    setFixedSize(pix.width(),pix.height());//调整按钮大小
    if(mask)
        setMask(pix.mask());//设置遮罩
    setStyleSheet("QPushButton{border:0px;}");//调整无边框
    setIcon(pix);//设置按钮图像
    setIconSize(QSize(pix.width(),pix.height()));//设置图像大小
}
MyPushButton::MyPushButton(QWidget* parent,QString name):QPushButton(name,parent)
{
    setCursor(Qt::PointingHandCursor);//设置鼠标形状

}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    QSound::play(":/res/Res/points.wav");

    move(x()+1,y()+1);

    // 创建一个 QGraphicsColorizeEffect 对象来实现遮罩效果
//    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect(this);
//    effect->setColor(Qt::darkGray);  // 设置遮罩的颜色

//    setGraphicsEffect(effect);  // 应用遮罩效果

    QPushButton::mousePressEvent(e);  // 调用基类的 mousePressEvent 函数处理默认行为

    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    setGraphicsEffect(nullptr);  // 清除遮罩效果

    move(x()-1,y()-1);

    return QPushButton::mouseReleaseEvent(e);
}
void MyPushButton::enterEvent(QEvent *event)
{
    QSound::play(":/res/Res/mouseMoveToButton.wav");

//    if(pressedImgPath!="")
//    {
//        QPixmap pix;
//        pix.load(pressedImgPath);
//        setIcon(pix);
//    }

    return QPushButton::enterEvent(event);
}

void MyPushButton::leaveEvent(QEvent *event)
{
//   if(pressedImgPath!="")
//   {
//        QPixmap pix;
//        pix.load(normalImgPath);
//        setIcon(pix);
//   }
   setGraphicsEffect(nullptr);  // 清除遮罩效果
   return QPushButton::leaveEvent(event);
}
