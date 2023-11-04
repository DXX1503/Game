#include "towerposition.h"
#include "selectbutton.h"

#include <QSize>
#include <QPainter>
#include <QPixmap>

 const QSize TowerPosition::m_fixedSize(TOWERPO_WIDTH,TOWERPO_HEIGHT);

TowerPosition::TowerPosition(QPoint pos,const QPixmap & sprite):
    m_hasTower(false),
    m_hasTower1(false),
    m_hasTower2(false),
    m_hasTower3(false),
    m_hasButton(false),
    m_hasButton2(false),
    m_pos(pos),
    m_sprite(sprite)
{
}

void TowerPosition::setHasTower(bool hasTower)
{
    m_hasTower=hasTower;
}

bool TowerPosition::hasTower()
{
    return m_hasTower;
}

void TowerPosition::setHasTower1(bool hasTower1)
{
    this->m_hasTower1=hasTower1;
    setHasTower(hasTower1);
}

bool TowerPosition::hasTower1()
{
    return m_hasTower1;
}

void TowerPosition::setHasTower2(bool hasTower2)
{
    this->m_hasTower2=hasTower2;
    setHasTower(hasTower2);
}

bool TowerPosition::hasTower2()
{
    return m_hasTower2;
}

void TowerPosition::setHasTower3(bool hasTower3)
{
    m_hasTower3=hasTower3;
    setHasTower(hasTower3);
}

bool TowerPosition::hasTower3()
{
    return m_hasTower3;
}

void TowerPosition::setHasButton(bool hasButton)
{
    m_hasButton=hasButton;
}

bool TowerPosition::hasButton()
{
    return m_hasButton;
}

void TowerPosition::setHasButton2(bool hasButton2)
{
    m_hasButton2=hasButton2;
}

bool TowerPosition::hasButton2()
{
    return m_hasButton2;
}

void TowerPosition::setHasUpdate1(bool hasUpdate1)
{
    m_hasUpdate1=hasUpdate1;
}

bool TowerPosition::hasUpdate1()
{
    return m_hasUpdate1;
}

void TowerPosition::setHasUpdate2(bool hasUpdate2)
{
    m_hasUpdtae2=hasUpdate2;
}

bool TowerPosition::hasUpdate2()
{
    return m_hasUpdtae2;
}

QPoint TowerPosition::centerPos() const
{
    QPoint tmp;
    tmp.setX(m_pos.x()+m_fixedSize.width()/2);
    tmp.setY(m_pos.y()+m_fixedSize.height()/2);
    return tmp;
}

bool TowerPosition::containPoint(const QPoint pos) const
{
    bool xInHere=(pos.x()>m_pos.x()) && (pos.x()<m_pos.x()+m_fixedSize.width());
    bool yInHere=(pos.y()>m_pos.y()) && (pos.y()<m_pos.y()+m_fixedSize.height());
    return xInHere && yInHere;
}

void TowerPosition::draw(QPainter *painter) const
{
    painter->drawPixmap(m_pos.x(),m_pos.y(),m_sprite);
}

QPoint TowerPosition::getPos()
{
    return this->m_pos;
}

void TowerPosition::setTower(Tower * tower)
{
    m_tower=tower;
}

void TowerPosition::setButton(selectButton *button)
{
    m_button=button;
}

void TowerPosition::setButton2(selectButton2 *button)
{
    m_button2=button;//我这里一开始写成了 m_hasButton2=button,赋值给错了，导致这个防御塔坑的私有成员m_button2==NULL,就进不去那个if结构
}

Tower * TowerPosition::get_tower()
{
    return m_tower;
}

selectButton2 * TowerPosition::getButton2()
{
    return m_button2;
}

void TowerPosition::setRemoveTower()
{
    setTower(NULL);
    setHasTower(false);
    setHasTower1(false);
    setHasTower2(false);
    setHasTower3(false);
    setHasUpdate1(false);
    setHasUpdate2(false);
}

selectButton * TowerPosition::getButton()
{
    return m_button;
}

int TowerPosition::getWidth()
{
    return m_fixedSize.width();
}

int TowerPosition::getHeight()
{
    return m_fixedSize.height();
}
