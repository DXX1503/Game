#include "selectbutton.h"

selectButton::selectButton(QPoint pos,MainWindow * game,int width,int height):
    m_game(game),
    m_pos(pos),
    m_width(width),
    m_height(height)
{
    m_selectBoxImagePath[0]=":/images/tower0.png";
    m_selectBoxImagePath[1]=":/images/tower2.png";
    m_selectBoxImagePath[2]=":/images/tower3.png";
}

selectButton::~selectButton()
{
    m_game=NULL;
}

void selectButton::draw(QPainter *painter) const
{
        painter->save();
        painter->drawPixmap(m_pos.x(),m_pos.y(),m_selectBoxImagePath[0]);
        painter->drawPixmap(m_pos.x()+35,m_pos.y(),m_selectBoxImagePath[1]);
        painter->drawPixmap(m_pos.x()+70,m_pos.y(),m_selectBoxImagePath[2]);
        painter->restore();
}

void selectButton::getRemoved()
{
    m_game->removeButton(this);

}

bool selectButton::containPos(QPoint pos)
{
    bool xInHere=pos.x()>m_pos.x() && pos.x()<m_pos.x()+m_width;
    bool yInHere=pos.y()>m_pos.y() && pos.y()<m_pos.y()+m_height;
    return xInHere&&yInHere;
}

QPoint selectButton::getPos()
{
    return m_pos;
}


