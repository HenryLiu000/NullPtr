#ifndef SETTING_H
#define SETTING_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"

class Setting:public QWidget{
    Q_OBJECT
public:
    explicit Setting(QWidget *parent = 0);
    ~Setting();
    void paintEvent(QPaintEvent *event);
    QSound* bgm;

};

#endif // SETTING_H
