#ifndef CARDSLOT_H
#define CARDSLOT_H
#include <QWidget>
#include <QPainter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "card.h"
class CardSlot:public QWidget
{
    Q_OBJECT
public:
    Qt::GlobalColor color;
    QHBoxLayout* cardSlotLayout;
    QList<MyCard*> cards;//MyCard(QPushButton内部的copy constructor被delete了，因此QList需要存放一堆指针！！)
    int lastnum = 0;//cardslot的最后一个元素是一个属性，直接让它成为成员变量!
public:
    explicit CardSlot(QWidget* parent,int ltx,int lty,int w,int h, Qt::GlobalColor Color = Qt::transparent);
    ~CardSlot();
    void paintEvent(QPaintEvent *event);
};
#endif // CARDSLOT_H
