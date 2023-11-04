#include "enemy.h"
#include "waypoint.h"
#include "mainwindow.h"
#include "utility.h"
#include "tower.h"

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QVector2D>

const QSize Enemy::m_fixedSize(22,23);

Enemy::Enemy(wayPoint * startWayPoint,MainWindow * game,const QPixmap & sprite):
    QObject(0),
    m_game(game),
    m_pos(startWayPoint->getPos()),
    m_sprite(sprite),
    m_ScoreAD(10)
{
    m_maxHp=40;
    m_currentHp=m_maxHp;
    m_walkingSpeed=1;
    m_active=false;
    m_destinationWayPoint=startWayPoint->getNextWayPoint();
}

Enemy::~Enemy()
{
    m_attackTowerList.clear();
    m_destinationWayPoint=NULL;
    m_game=NULL;
}


//怪物血条
void Enemy::draw(QPainter *painter) const
{
    if(!m_active)
    {
        return ;
    }
    painter->save();
    static const int healthBarWidth=m_fixedSize.width();
    QPoint healthBarPoint=m_pos+QPoint(-m_fixedSize.width()/2,-m_fixedSize.height());
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,2));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::blue);
    QRect healthBarRect(healthBarPoint,QSize((double)m_currentHp/m_maxHp*healthBarWidth,2));
    painter->drawRect(healthBarRect);

    QPoint tmp(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2);
    painter->drawPixmap(tmp.x(),tmp.y(),m_sprite);
    painter->restore();
}

void Enemy::move()
{
    if(!m_active)
    {
        return ;
    }
    if(collisionWithCircle(m_pos,1,m_destinationWayPoint->getPos(),1))//到达了航点
    {
        if(m_destinationWayPoint->getNextWayPoint())//如果还有下一个航点
        {
            m_pos=m_destinationWayPoint->getPos();
            m_destinationWayPoint=m_destinationWayPoint->getNextWayPoint();
        }
        else//没有下一个航点，代表进入基地
        {
            m_game->getHpDamage();
            m_game->removeEnemy(this);
            return ;
        }
    }
    else
    {
        QPoint targetPoint=m_destinationWayPoint->getPos();
        double movementSpeed=m_walkingSpeed;
        QVector2D normalized(targetPoint-m_pos);
        normalized.normalize();
        m_pos=m_pos+normalized.toPoint()*movementSpeed;
    }
}

int Enemy::getm_ScoreAD()
{
    return m_ScoreAD;
}

void Enemy::doActive()
{
    m_active=true;
}

QPoint Enemy::get_pos()
{
    return m_pos;
}

void Enemy::getAttack(Tower *tower)
{
    m_attackTowerList.push_back(tower);
}

void Enemy::getDamage(int damage)
{
    m_currentHp-=damage;
    if(m_currentHp<=0)
    {
        m_game->awardGlod();
        getRemoved();
    }
}

void Enemy::getRemoved()
{
    if(m_attackTowerList.empty())
    {
        return ;
    }
    else
    {
        foreach(Tower * tower,m_attackTowerList)
            tower->targetKilled();
        m_game->removeEnemy(this);
    }
}

void Enemy::getLostSight(Tower *tower)
{
    m_attackTowerList.removeOne(tower);
}

void Enemy::reSetHp(int maxHp)
{
    m_maxHp=maxHp;
    m_currentHp=maxHp;
}
