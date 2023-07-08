#ifndef CARD_H
#define CARD_H

#include <QLabel>
#include <QMovie>
#include <QSound>
#include <QTimer>
#include <QPushButton>
#include <QGraphicsColorizeEffect>
#include <QPainter>
class MyCard:public QPushButton{
    Q_OBJECT
public:
    bool is_play=0;  //记录是否打出了这张牌，如果打出了就不可与鼠标进行交互
    bool is_clicked = 0;
    int heads_num;
    int card_number;
    QString card_Path;
    MyCard(QWidget* parent,int _number,int w,int h);
    //copy constructor was deleted by Qt official;
    //Don't write it again
    ~MyCard();
    void mousePressEvent(QMouseEvent *e);
    //void mouseReleaseEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *event);
};

#endif // CARD_H
