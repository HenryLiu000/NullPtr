#include "cardslot.h"
#include <QDebug>
CardSlot::CardSlot(QWidget* parent,int ltx,int lty,int w,int h,Qt::GlobalColor Color):QWidget(parent),color(Color)
{
    cardSlotLayout = new QHBoxLayout(this);
    cardSlotLayout->setAlignment(Qt::AlignLeft);
    cardSlotLayout->setContentsMargins(0,0,0,0);
    cardSlotLayout->setSpacing(0);
    setLayout(cardSlotLayout);
    this->move(ltx,lty);
    setFixedSize(w,h);
}
CardSlot::~CardSlot()
{
    for(auto it:this->cards)
    {
        if(it != NULL)
        {
            delete it;
        }
    }
    cards.clear();
    delete cardSlotLayout;
}
void CardSlot::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(),color);
}
