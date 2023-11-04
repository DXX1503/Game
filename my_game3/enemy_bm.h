#ifndef ENEMY_BM_H
#define ENEMY_BM_H

#include <QObject>

#include "enemy_base.h"


class enemy_Bm : public Enemy_base
{
    Q_OBJECT
public:
    explicit enemy_Bm(QObject *parent = nullptr);
    enemy_Bm(wayPoint * start,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/monster2.png"));
    ~enemy_Bm();
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
private slots:
    void doActive();
};

#endif // ENEMY_BM_H
