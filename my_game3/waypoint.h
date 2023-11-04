#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <QPoint>
#include <QPainter>

class wayPoint
{
public:
    wayPoint(QPoint pos);


    void setNextWayPoint(wayPoint * nextWaypoint);

    wayPoint * getNextWayPoint();

    const QPoint getPos();

    void draw(QPainter * painter) const;
private:
    QPoint m_pos;
    wayPoint * m_nextWayPoint;
};

#endif // WAYPOINT_H
