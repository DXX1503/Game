#include "bullet.h"
#include "tower.h"
#include "mainwindow.h"
#include "utility.h"
#include "enemy.h"

#include <QPoint>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>


const QSize Bullet::m_fixedSize(BULLET_WIDTH,BULLET_HEIGHT);

Bullet::Bullet()
{
}
Bullet::Bullet(QPoint startPos,QPoint targetPos,int damage,Enemy * enemy,MainWindow * game,const QPixmap & sprite):
    m_startPos(startPos),
    m_targetPos(targetPos),
    m_currentPos(startPos),
    m_damage(damage),
    m_sprite(sprite),
    m_targetEnemy(enemy),
    m_game(game)

{
}

QPoint Bullet::getCurrentPos()
{
    return m_currentPos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos=pos;
}

void Bullet::move()
{
    static int duration=100;
    QPropertyAnimation * animation =new QPropertyAnimation(this,"m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    animation->start();
}

void Bullet::hitTarget()
{
    if(m_game->getEnemyList().indexOf(m_targetEnemy)!=-1)
        m_targetEnemy->getDamage(m_damage);
    m_game->removeBullet(this);
}

void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos,m_sprite);
}
