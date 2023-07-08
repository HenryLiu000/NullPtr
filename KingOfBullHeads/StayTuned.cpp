#include "StayTuned.h"
StayTuned::StayTuned(QWidget *parent):QWidget(parent)
{
    setFixedSize(800,500);
    sure = new MyPushButton(this, 0, ":/button/button14.png", ":/button/button14.png");
    sure->move(300,370);
    sure->setIconSize(QSize(180,540));
    slogan = new QLabel(this);
    slogan->setText("敬请期待");
    slogan->setAlignment(Qt::AlignCenter);
    slogan->move(200,150);
    slogan->setStyleSheet("font-size: 40px");
    slogan->setFixedSize(160,200);
    slogan->show();

}
StayTuned::~StayTuned()
{
    delete sure;
    delete slogan;
}
void StayTuned::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    int red = 253;
    int green = 197;
    int blue = 0;
    QColor targetColor(red, green, blue);
    painter.fillRect(rect(), targetColor);
}
