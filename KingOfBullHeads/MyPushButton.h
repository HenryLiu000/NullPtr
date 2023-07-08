#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QGraphicsColorizeEffect>
#include <QMouseEvent>

class MyPushButton:public QPushButton{
    Q_OBJECT
public:
    MyPushButton(QWidget* parent,bool mask,QString normalImg,QString pressedImg="");
    MyPushButton(QWidget* parent,QString name);
    QString normalImgPath;
    QString pressedImgPath;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // MYPUSHBUTTON_H
