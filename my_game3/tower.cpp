#include "tower.h"
#include "mainwindow.h"
#include "utility.h"
#include "bullet.h"
#include "enemy.h"


#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QVector2D>
#include <QtMath>


const QSize Tower::m_fixedSize(TOWER_WIDTH,TOWER_HEIGHT);

Tower::Tower()
{}

Tower::Tower(QPoint pos,MainWindow * game, const QPixmap & sprite,int damage):
    m_attacking(false),
    m_attackRange(75),
    m_damage(damage),
    m_fireRate(1000),
    m_level(1),
    m_chooseEnemy(NULL),
    m_game(game),
    m_pos(pos),
    m_sprite(sprite)
{
    m_fireRateTime=new QTimer(this);
    connect(m_fireRateTime,SIGNAL(timeout()),this,SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete m_fireRateTime;
    m_fireRateTime=NULL;
    m_chooseEnemy=NULL;
    m_game=NULL;
    delete m_chooseEnemy;
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(m_pos,m_attackRange,m_attackRange);
    painter->drawText(QRect(this->m_pos.x()-30,this->m_pos.y()+15,100,25),QString("level: %1").arg(m_level));//把防御塔的等级画出来
    painter->drawPixmap(m_pos.x()-m_fixedSize.width()/2,m_pos.y()-m_fixedSize.height()/2-10,m_sprite);
}

void Tower::chooseEnemyFromAttack(Enemy *enemy)
{
    m_chooseEnemy=enemy;
    attackEnemy();
    m_chooseEnemy->getAttack(this);
}

void Tower::attackEnemy()
{
    m_fireRateTime->start(m_fireRate);
}

void Tower::shootWeapon()
{
    Bullet * bullet=new Bullet(m_pos,m_chooseEnemy->get_pos(),m_damage,m_chooseEnemy,m_game);
    bullet->move();
    m_game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();
}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->getLostSight(this);
    if(m_chooseEnemy)
    {
        m_chooseEnemy=NULL;
    }
    m_fireRateTime->stop();
}

void Tower::checkEnemyInRange()
{
    if(m_chooseEnemy)//如果有了攻击的敌人
    {
        QVector2D normalized(m_chooseEnemy->get_pos()-m_pos);
        normalized.normalize();
        if(!collisionWithCircle(m_pos,m_attackRange,m_chooseEnemy->get_pos(),1))
        {
            lostSightOfEnemy();
        }
    }
    else
    {
        QList<Enemy * > enemyList=m_game->getEnemyList();
        foreach(Enemy * enemy,enemyList)
            if(collisionWithCircle(m_pos,m_attackRange,enemy->get_pos(),1))
            {
                chooseEnemyFromAttack(enemy);
                break;
            }
    }
}

void Tower::reSetDamage(int damage)
{
    m_damage=damage;
}

void Tower::levelChange()
{
    m_level++;
}

int Tower::getLevel()
{
    return m_level;
}

int Tower::getDamgae()
{
    return m_damage;
}

Enemy * Tower::getAttackEnemy()
{
    return m_chooseEnemy;
}

void Tower::getRemoved()
{
    if(getAttackEnemy())
    {
        getAttackEnemy()->getLostSight(this);
    }
    m_game->removeTower(this);
}

