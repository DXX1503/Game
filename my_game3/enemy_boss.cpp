#include "enemy_boss.h"

const QSize enemy_Boss::m_fixedSize(22,23);
enemy_Boss::enemy_Boss(QObject *parent) : Enemy_base(parent)
{
}

enemy_Boss::enemy_Boss(wayPoint *start, MainWindow *game, const QPixmap &sprite)
{
}

enemy_Boss::~enemy_Boss()
{
}

void enemy_Boss::draw(QPainter *painter) const
{
    if(!m_active)
    {
        return;
    }
    painter->save();
    static const int healthBarWidth=m_fixedSize.width();
    QPoint healthBarPoint=m_pos+QPoint(- m_fixedSize.width()/2,-m_fixedSize.height());
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

void enemy_Boss::move()
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
            m_game->removeEnemy((Enemy*)this);
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

QPoint enemy_Boss::get_pos()
{
    return m_pos;
}

void enemy_Boss::getAttack(Tower *tower)
{
    m_attackTowerList.push_back(tower);
}

void enemy_Boss::getDamage(int damage)
{
    m_currentHp-=damage;
    if(m_currentHp<=0)
    {
        m_game->awardGlod();
        getRemoved();
    }
}

void enemy_Boss::getRemoved()
{
    if(m_attackTowerList.empty())
    {
        return ;
    }
    else
    {
        foreach(Tower * tower,m_attackTowerList)
        tower->targetKilled();
        m_game->removeEnemy((Enemy*)this);
    }
}

void enemy_Boss::getLostSight(Tower *tower)
{
    m_attackTowerList.removeOne(tower);
}

void enemy_Boss::reSetHp(int maxHp)
{
    m_maxHp=maxHp;
    m_currentHp=maxHp;
}

int enemy_Boss::getm_ScoreAD()
{
    return m_ScoreAD;
}

void enemy_Boss::doActive()
{
    m_active=true;
}
