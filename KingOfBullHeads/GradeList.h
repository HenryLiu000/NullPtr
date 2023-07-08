#ifndef GRADELIST_H
#define GRADELIST_H
#include<QObject>
#include<QLabel>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSize>
#include"MyPushButton.h"

class GradeList : public QWidget
{
    Q_OBJECT
public:
    explicit GradeList(QWidget *parent = 0);
    ~GradeList();
    void paintEvent(QPaintEvent *event);
    QPushButton *sure;
    QLabel* title;
    QLabel* Player[4];
    QLabel* Score[4];

signals:

public slots:

};
#endif // GRADELIST_H
