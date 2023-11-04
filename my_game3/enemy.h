#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QSize>

#include "waypoint.h"
#include "mainwindow.h"
#include "tower.h"



class MainWindow;
class Tower;
class QPainter;
class wayPoint;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(wayPoint * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster2.png"));
    ~Enemy();
    void draw(QPainter * painter) const;
    void move();
    int getm_ScoreAD();

    QPoint get_pos();

    void getAttack(Tower * tower);
    void getDamage(int damage);
    void getRemoved();
    void getLostSight(Tower * tower);
    void reSetHp(int maxHp);


private slots:
    void doActive();
private:
    int m_maxHp;
    int m_currentHp;
    int m_walkingSpeed;
    bool m_active;

    wayPoint * m_destinationWayPoint;
    MainWindow * m_game;
    QPoint m_pos;
    QPixmap m_sprite;
    QList<Tower *> m_attackTowerList;

    static const QSize m_fixedSize;
    //死亡后的积分值
    int m_ScoreAD;

};

#endif // ENEMY_H
