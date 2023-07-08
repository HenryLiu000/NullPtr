#ifndef RULE_H
#define RULE_H

#endif // RULE_H

#include<QObject>
#include <QWidget>
#include<QImage>
#include<QPainter>
#include <QLabel>
#include<QSound>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include"MyPushButton.h"
class RuleScene:public QWidget
{
    Q_OBJECT
public:
    explicit RuleScene(QWidget *parent = 0);
    ~RuleScene();
    void paintEvent(QPaintEvent *event);
    QSound* bgm;
    QLabel* ruleText;
    QPushButton *Quit;
signals:

public slots:


};
