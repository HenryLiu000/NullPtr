#include "GradeList.h"
GradeList::GradeList(QWidget *parent):QWidget(parent)
{
    setFixedSize(1200,750);
    sure = new MyPushButton(this,0,":/button/button14.png", ":/button/button14.png");
    sure->move(360,550);
    sure->setIconSize(QSize(270,810));
    title = new QLabel(this);
    title->setFixedSize(200,80);
    title->setAlignment(Qt::AlignCenter);
    title->move(450,50);
    title->setStyleSheet("font-size: 40px");
    for(int i = 0;i < 4;i++)
    {
        Player[i] = new QLabel(this);
        Score[i] = new QLabel(this);
    }
}
GradeList::~GradeList()
{
    delete title;
    delete sure;
    for(int i = 0;i < 4;i++)
    {
        delete Player[i];
        delete Score[i];
    }

}
void GradeList::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    int red = 253;
    int green = 197;
    int blue = 0;
    QColor targetColor(red, green, blue);
    painter.fillRect(rect(), targetColor);
}
