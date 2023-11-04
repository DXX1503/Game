#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QObject>

#include "mainwindow.h"

class MainWindow;

class selectButton :QObject
{
    Q_OBJECT
private:
    MainWindow * m_game;
    QPoint m_pos;
    int m_width;
    int m_height;
    QString m_selectBoxImagePath[3];
public:
    selectButton(QPoint pos,MainWindow * game,int width=105,int height=35);
    ~selectButton();
    void draw(QPainter * painter)const;
    void getRemoved();//选择框被点了一次，就要移除
    bool containPos(QPoint pos);//判断这次的点击是否在我的选择框内
    QPoint getPos();
};

#endif // SELECTBUTTON_H
