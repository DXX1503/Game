#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QSize>

#include "enemy.h"
#include "tower.h"
#include "mainwindow.h"

class Enemy;
class MainWindow;
class Tower;


class Bullet:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ getCurrentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos,QPoint targetPos,int damage,Enemy * enemy,MainWindow * game,const QPixmap & sprite=QPixmap(":/images/bullet.png"));
    Bullet();
    QPoint getCurrentPos();
    void setCurrentPos(QPoint pos);

    void move();
    void draw(QPainter * painter) const;

private slots:
    void hitTarget();
private:
    QPoint m_startPos;
    QPoint m_targetPos;
    QPoint m_currentPos;
    int m_damage;
    QPixmap m_sprite;

    Enemy * m_targetEnemy;
    MainWindow * m_game;
    static const QSize m_fixedSize;

};

#endif // BULLET_H
