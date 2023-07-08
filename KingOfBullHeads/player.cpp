#include "player.h"
#include "ui_mainwindow.h"

MyPlayer::MyPlayer(QWidget *parent, QString _name, QString _PATH):QLabel(parent),player_name(_name),avatar_PATH(_PATH)
{
    cards_num = 10;
    heads_num = 0;
//    setCursor(Qt::PointingHandCursor);//设置鼠标形状
    QPixmap pix;
    bool ret=pix.load(avatar_PATH);//加载图片
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }
    pix= pix.scaled(pix.size()*0.2);//改变图片大小
    setFixedSize(pix.width(),pix.height());//调整QLabel大小
    setStyleSheet("QPushButton{border:0px;}");//调整无边框
    setPixmap(pix);
}


