#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QSize>

#include "waypoint.h"
#include "mainwindow.h"
#include "tower.h"
#include "utility.h"

class Enemy_base : public QObject
{
    Q_OBJECT
public:
    explicit Enemy_base(QObject *parent = nullptr);
//    Enemy_base():blood(0),move_speed(0),damagetotower(0){};
    virtual ~Enemy_base();
    virtual void draw(QPainter * painter) const;
    virtual void move();

    virtual QPoint get_pos();
    virtual void getAttack(Tower * tower);
    virtual void getDamage(int damage);
    virtual void getRemoved();
    virtual void getLostSight(Tower * tower);
    virtual void reSetHp(int maxHp);
    virtual int  getm_ScoreAD();
protected slots:
    virtual void doActive();
protected:
    int m_maxHp;
    int m_currentHp;
    int m_walkingSpeed;
    bool m_active;

    wayPoint * m_destinationWayPoint;
    MainWindow * m_game;
    QPoint m_pos;
    QPixmap m_sprite;
    QList<Tower *> m_attackTowerList;
private:
    static const QSize m_fixedSize;
public:
    int m_ScoreAD;

};

#endif // ENEMY_BASE_H
