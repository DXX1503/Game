#ifndef ENEMY_NORMAL_H
#define ENEMY_NORMAL_H

#include <QObject>
#include <QPainter>
#include "enemy_base.h"
class Enemy_normal : public Enemy_base
{
    Q_OBJECT
public:
    explicit Enemy_normal(QObject *parent = nullptr);
    Enemy_normal(wayPoint * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster2.png"));
    ~Enemy_normal();
    void draw(QPainter * painter) const;
    void move();

    QPoint get_pos();

    void getAttack(Tower * tower);
    void getDamage(int damage);
    void getRemoved();
    void getLostSight(Tower * tower);
    void reSetHp(int maxHp);
    virtual int getm_ScoreAD();
    static const QSize m_fixedSize;

signals:
protected slots:
    void doActive();

};

#endif // ENEMY_NORMAL_H
