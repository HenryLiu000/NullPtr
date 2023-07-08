#include <QDebug>
#include "settings.h"

SettingScene::SettingScene(QWidget *parent):QWidget(parent)
{

    Quit = new MyPushButton(this, 0, ":/button/button01.png", ":/button/button01.png");
    Quit->resize(300,100);
    Quit->move(650,900);
    Quit->setStyleSheet("font-size: 40px");

    setVolume = new QSlider(Qt::Horizontal,parent);
    setVolume->setFixedWidth(500);
    setVolume->setValue(70);
    setVolume->move(600,300);
    setVolume->show();

}

void SettingScene::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/playbackground.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
SettingScene::~SettingScene()
{
    delete setVolume;
    delete Quit;
}
