#ifndef SELECTBUTTON2_H
#define SELECTBUTTON2_H

//升级按钮
#include <QPainter>
#include <QRect>
#include <QPoint>

#include "mainwindow.h"
#include "tower.h"

class MainWindow;
class Tower;

class selectButton2:QObject
{
    Q_OBJECT
private:
    MainWindow * m_game;
    Tower * m_tower;
    QPoint m_pos;
    int m_width;
    int m_height;
public:
    selectButton2(QPoint pos,MainWindow* game,int width,int height);
    ~selectButton2();
    void draw(QPainter * painter)const;
    void getRemoved();
    Tower * getTower();
    void setTower(Tower *tower);
    bool containPos(QPoint pos);
    QPoint getPos();
};

#endif // SELECTBUTTON2_H
