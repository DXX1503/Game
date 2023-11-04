#ifndef ENEMY_BOSS_H
#define ENEMY_BOSS_H

#include <QObject>

#include "enemy_base.h"

class enemy_Boss : public Enemy_base
{
    Q_OBJECT
public:
    explicit enemy_Boss(QObject *parent = nullptr);
    enemy_Boss(wayPoint * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster2.png"));
    ~enemy_Boss();
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

#endif // ENEMY_BOSS_H
