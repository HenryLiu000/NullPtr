#ifndef STAYTUNED_H
#define STAYTUNED_H
#include<QObject>
#include<QLabel>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"

class StayTuned : public QWidget
{
    Q_OBJECT
public:
    explicit StayTuned(QWidget *parent = 0);
    ~StayTuned();
    void paintEvent(QPaintEvent *event);
    QPushButton *sure;
    QLabel *slogan;
signals:

public slots:

};
#endif // STAYTUNED_H
