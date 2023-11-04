#include "waypoint.h"

wayPoint::wayPoint(QPoint pos):
    m_pos(pos),
    m_nextWayPoint(NULL)
{
}

void wayPoint::setNextWayPoint(wayPoint *nextWaypoint)
{
    m_nextWayPoint=nextWaypoint;
}

wayPoint * wayPoint::getNextWayPoint()
{
    return m_nextWayPoint;
}

const QPoint wayPoint::getPos()
{
    return m_pos;
}

void wayPoint::draw(QPainter *painter) const
{
//    painter->save();
//    painter->setPen(Qt::green);
//    painter->drawEllipse(m_pos,4,4);
//    painter->drawEllipse(m_pos,1,1);
//    if(m_nextWayPoint)//如果存在下一个航点就可以画起来
//    {
//        painter->drawLine(m_pos,m_nextWayPoint->getPos());
//    }
//    painter->restore();
}

