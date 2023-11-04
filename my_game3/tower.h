#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

#include "enemy.h"
#include "mainwindow.h"

class QPainter;
class Enemy;
class MainWindow;
class QTimer;


class Tower :QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,MainWindow * game,const QPixmap & sprite,int damage);
    ~Tower();
    Tower();

    void draw(QPainter * painter)const;

    void attackEnemy();
    void targetKilled();
    void chooseEnemyFromAttack(Enemy * enemy);
    void removeBullet();
    void lostSightOfEnemy();
    void checkEnemyInRange();
    void reSetDamage(int damage);
    int getDamgae();
    void levelChange();
    int getLevel();

    void getRemoved();

    Enemy * getAttackEnemy();

protected slots:
    void shootWeapon();

protected:
    bool m_attacking;
    int m_attackRange;
    int m_damage;
    int m_fireRate;
    int m_level;

    Enemy * m_chooseEnemy;
    MainWindow * m_game;
    QTimer * m_fireRateTime;

    const QPoint m_pos;//这个pos是中心点，左上
    const QPixmap m_sprite;

    static const QSize m_fixedSize;

};

#endif // TOWER_H
