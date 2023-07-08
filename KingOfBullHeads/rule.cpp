#include <QDebug>
#include "rule.h"

RuleScene::RuleScene(QWidget *parent):QWidget(parent)
{
    bgm = new QSound(":/res/Res/bgm01.wav");
    bgm->setLoops(-1);
    //bgm->play();刷夜不放

    Quit = new MyPushButton(this, 0, ":/button/button01.png", ":/button/button01.png");
    Quit->resize(300,100);
    Quit->move(650,900);
    Quit->setStyleSheet("font-size: 40px");

    ruleText=new QLabel(parent);
    ruleText->setText("游戏使用一副由 104 张牌组成的牌堆，编号从 1 到 104。每张牌上都有1到7\n"
"个牛头。在游戏开始时，将四张牌面朝上放置在桌子中央。这些牌作为每一行\n"
"的起始点。玩家按顺时针方向轮流进行。在自己的回合中，玩家必须将一张牌\n"
"放在任意一行上。被放置的牌必须比该行中的最后一张牌大，但要比下一张更\n"
"高的牌小。如果玩家的牌使得某行达到六张，他们必须拿取整个行，并将其加\n"
"入自己的得分堆。然后，玩家用所放的牌开始新的一行。如果玩家打出的牌比\n"
"所有已放置的牌都要小，他们必须拿取带有最低牌值的行。当所有玩家出完牌\n"
"后，游戏结束。此时，所有玩家计算他们的牛头点数，牛头点数最少的玩家获\n"
"胜。\n");
    ruleText->setFixedSize(1500,500);
    ruleText->setStyleSheet("font-size: 40px");
    ruleText->setAlignment(Qt::AlignTop);
    ruleText->move(100,300);
    ruleText->show();

}

void RuleScene::paintEvent(QPaintEvent *event)
{//此函数只能命名为paintEvent，是QWidget的虚函数
    QWidget::paintEvent(event);
    QPainter painter(this);
    // 加载照片文件
    QImage image(":/res/Res/playbackground.png");
    // 在绘图设备上绘制照片
    painter.drawImage(rect(), image);
}
RuleScene::~RuleScene()
{
    delete bgm;
    delete ruleText;
    delete Quit;
}
