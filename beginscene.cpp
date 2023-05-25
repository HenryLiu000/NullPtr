#include "beginscene.h"

BeginScene::BeginScene(QWidget *parent):QWidget(parent){
    bgm=new QSound(":/res/Res/bgm1.wav");
    bgm->setLoops(-1);

    MyPushButton* begin2game = new MyPushButton(this,true,":/res/Res/Icon.png",":/res/Res/victory.png");
    begin2game->move(100, 100);
    connect(begin2game, &MyPushButton::clicked, [=](){
        bgm->stop();
        emit Begin2Game();
    });
}

void BeginScene::ShowBGI(QPaintEvent *event){
    QWidget::paintEvent(event);

    QPainter painter(this);

    // 加载照片文件
    QImage image(":/res/Res/Icon.ico");

    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
