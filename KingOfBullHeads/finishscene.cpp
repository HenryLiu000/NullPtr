#include "finishscene.h"

FinishScene::FinishScene(QWidget* parent):QWidget(parent){
    //设置结算动画
//    backgroundmovie=new QMovie(":/res/Res/victoryBull.gif");
//    thisbackground->setMovie(backgroundmovie);
//    backgroundmovie->start();
    //设置确认按钮
    Confirm = new MyPushButton(this, "确认");
    Confirm->setFixedSize(200, 80);
    Confirm->setStyleSheet("font-size: 40px");
    Confirm->move(550, 500);
}
