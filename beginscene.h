#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include"MyPushButton.h"

class BeginScene : public QWidget
{
    Q_OBJECT
public:
    explicit BeginScene(QWidget *parent = 0);
    void ShowBGI(QPaintEvent *event);
    QSound* bgm;

signals:
    void Begin2Game();

public slots:
};

#endif // BEGINSCENE_H
