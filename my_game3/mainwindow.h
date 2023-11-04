#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QString>
#include <QMediaPlayer>
#include <QPushButton>


#include "towerposition.h"
#include "tower.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "ui_mainwindow.h"
#include "selectbutton.h"
#include "selectbutton2.h"
#include <QDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class mainwindow; }
QT_END_NAMESPACE


#define BULLET_WIDTH   5
#define BULLET_HEIGHT  5
#define TOWERCOST1      300
#define TOWERCOST2      400
#define TOWERCOST3      500
#define TOWER_UP1_COST  300
#define TOWER_UP2_COST  400
#define TOWER_WIDTH      35
#define TOWER_HEIGHT     35
#define TOWERPO_WIDTH    35
#define TOWERPO_HEIGHT   35


class Bullet;
class Tower;
class Enemy;
class TowerPosition;
class selectButton;
class selectButton2;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr,QString username="");
    ~MainWindow();

    void loadTowerPosition1();
    void addWayPoint1();

    void loadTowerPosition2();
    void addWayPoint2();

    void loadTowerPosition3();
    void addWayPoint3();



    bool canBuyTower1();
    bool canBuyTower2();
    bool canBuyTower3();

    bool canUpdate1();
    bool canUpdate2();


    void getHpDamage();
    void awardGlod();
    void drawHp(QPainter * painter)const;
    void drawGlod(QPainter * painter)const;
    void drawWaves(QPainter * painter)const;
    void doGameOver();
    void removeEnemy(Enemy * enemy);
    void removeBullet(Bullet * bullet);
    void removeButton(selectButton * button);
    void removeButton2(selectButton2 * button);
    void removeTower(Tower * tower);
    void addBullet(Bullet * bullet);
    void setTitle(int n);
    void playmusic();


    QString getPath();
    void setPath(QString path);

    bool loadWaves();

    QList<Enemy *>  getEnemyList();

protected:
     void paintEvent(QPaintEvent *);
     void mousePressEvent(QMouseEvent *);

private slots:
     void updateMap();
     void gameStart();
     void v_show();
private:
    Ui::mainwindow *ui;
    QList<TowerPosition > m_towerPositionList;
    QList<Tower *> m_towerList;
    QList<wayPoint*> m_wayPointList;
    QList<Enemy *> m_enemyList;
    QList<Bullet *>m_bulletList;
    QList<selectButton *> m_selectButtonList;
    QList<selectButton2 *> m_selectButton2List;
    QPushButton * btn=new QPushButton();

private:
    int m_waves;//当前的波数


    bool m_gameWin;
    bool m_gameEnd;

    int m_playerHp;
    int m_playerGlod;

    QString m_path;
    QMediaPlayer *sound;
    QString m_userrnaame;
    int m_score;

};
#endif // MAINWINDOW_H
