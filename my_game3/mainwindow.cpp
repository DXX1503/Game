#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enemy.h"
#include "tower.h"
#include "waypoint.h"
#include "utility"
#include "selectbutton.h"
#include "selectbutton2.h"
#include "startfrom.h"
#include "reallystartform.h"
#include "CMySql.h"

#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QPoint>
#include <QTimer>
#include <QString>
#include <QMediaPlayer>
#include <QDialog>
#include <QMessageBox>
#include <QFont>
#include <QSound>


static const int tower1Cost=TOWERCOST1;
static const int tower2Cost=TOWERCOST2;
static const int tower3Cost=TOWERCOST3;

static const int towerupdate1Cost=TOWER_UP1_COST;
static const int towerupdate2Cost=TOWER_UP2_COST;


MainWindow::MainWindow(QWidget *parent,QString username):
     QMainWindow(parent),
     ui(new Ui::mainwindow),
     m_waves(0),
     m_gameWin(false),
     m_gameEnd(false),
     m_playerHp(5),
     m_playerGlod(1000),
     sound(nullptr),
     //传递用户名，用于修改积分
     m_userrnaame(username),
     m_score(0)
{
//    this->setFixedSize(750,375);
    this->setFixedSize(1500,750);
//    setWindowTitle("作者都不知道该如何称呼这款作品");
    btn->setParent(this);
//    btn->setFixedSize(50,20);
//    btn->move(700,0);

    btn->setFixedSize(50*2,20*2);
    btn->move(700*2,0);
    btn->setText("退出");
    btn->show();
    ui->setupUi(this);

    playmusic();
    QTimer * timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMap()));
    connect(btn,SIGNAL(clicked()),this,SLOT(v_show()));
    timer->start(30);
    QTimer::singleShot(300,this,SLOT(gameStart()));
}

void MainWindow::gameStart()
{
    loadWaves();
}

void MainWindow::v_show()
{
    StartFrom * p=new StartFrom();
    this->close();
    p->show();
    delete this;
}


void MainWindow::updateMap()
{
    foreach(Enemy * enemy,m_enemyList)
        enemy->move();
    foreach(Tower * tower,m_towerList)
        tower->checkEnemyInRange();
    update();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{    
    if(m_gameEnd || m_gameWin)
    {
        QPainter painter(this);
        QString path;
        if(m_gameEnd)
        {
            painter.save();
            qDebug()<<"本局积分："<<m_score<<endl;
            //失败本局没有积分
            m_score=0;
           path=":/img/images/Fictory.jpg";
           QPixmap fictory(path);
//           fictory=fictory.scaled(750,375,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
           fictory=fictory.scaled(1500,750,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
           painter.drawPixmap(0,0,fictory.width(),fictory.height(),fictory);
           painter.restore();
           return ;
        }
        else if(m_gameWin)
        {
            painter.save();
            path=":/img/images/Victory.jpg";
            QPixmap fictory(path);
//            fictory=fictory.scaled(750,375,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            fictory=fictory.scaled(1500,750,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            painter.drawPixmap(0,0,fictory.width(),fictory.height(),fictory);

            //将本局积分加载到数据库中（通关之后有积分，失败无积分）
            //记录本局积分的变量 m_score

            CMySql conn("utf8");
            char peer[MAX_ERR_LEN]={0};
            if(!conn.ConnectMySql("localhost","root","142986","test",3306,peer))
            {
                QMessageBox::critical(nullptr,"error",QString("error: ")+peer);
                return;
            }


            //p.show();
            QString sql1=QString("update TF_user set scoer = %1 where name = '"+m_userrnaame +"';").arg(m_score);
            qDebug()<<sql1<<endl;
            qDebug()<<m_userrnaame<<endl;
            vector<vector<string>> res;
            if(!conn.SelectMySql(sql1.toStdString().c_str(),res,peer))
            {
                qDebug()<<"error "<<peer<<endl;
            }
            conn.DisConnect();

            painter.restore();
            //-------------------------------------------------------------------------
            return ;
        }
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),getPath());
    foreach(const TowerPosition & towerPos,m_towerPositionList)
    {
        if(!towerPos.m_hasTower)
        {
            towerPos.draw(&painter);
        }
    }
    foreach(const Tower * tower,m_towerList)
        tower->draw(&painter);

    foreach(const wayPoint * waypoint,m_wayPointList)
        waypoint->draw(&painter);

    foreach(const Enemy * enemy,m_enemyList)
        enemy->draw(&painter);

    foreach(const Bullet * bullet,m_bulletList)
        bullet->draw(&painter);

    foreach(const selectButton * button,m_selectButtonList)
        button->draw(&painter);

    foreach(const selectButton2 * button2,m_selectButton2List)
        button2->draw(&painter);

    drawHp(&painter);
    drawGlod(&painter);
    drawWaves(&painter);
}

void MainWindow::loadTowerPosition1()//加载防御塔坑的位置
{
    QPoint pos[]=
    {
        QPoint(86,98),
        QPoint(226,98),
        QPoint(439,98),
        QPoint(105,215),
        QPoint(186,215),
        QPoint(314,215),
        QPoint(105,321),
        QPoint(223,323),
        QPoint(365,319)
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint1()
{
    wayPoint * waypoint1=new wayPoint(QPoint(79,6));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(79,55));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(407,55));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(407,175));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(83,175));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(83,292));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

    wayPoint * waypoint7=new wayPoint(QPoint(473,292));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);
}

void MainWindow::loadTowerPosition2()
{
    QPoint pos[]=
    {
//        QPoint(171,240),
//        QPoint(251,240),
//        QPoint(325,240),
//        QPoint(270,170),
//        QPoint(345,170),
//        QPoint(420,170),
//        QPoint(245,100),
//        QPoint(520,170),

        QPoint(171*2,240*2),
        QPoint(251*2,240*2),
        QPoint(325*2,240*2),
        QPoint(270*2,170*2),
        QPoint(345*2,170*2),
        QPoint(420*2,170*2),
        QPoint(245*2,100*2),
        QPoint(520*2,170*2),
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }
}

void MainWindow::addWayPoint2()
{
//    wayPoint * waypoint1=new wayPoint(QPoint(177,371));
    wayPoint * waypoint1=new wayPoint(QPoint(177*2,371*2));
    m_wayPointList.push_back(waypoint1);

//    wayPoint * waypoint2=new wayPoint(QPoint(177,292));
    wayPoint * waypoint2=new wayPoint(QPoint(177*2,292*2));
    waypoint1->setNextWayPoint(waypoint2);
    m_wayPointList.push_back(waypoint2);

//    wayPoint * waypoint3=new wayPoint(QPoint(388,292));
    wayPoint * waypoint3=new wayPoint(QPoint(388*2,292*2));
    waypoint2->setNextWayPoint(waypoint3);
    m_wayPointList.push_back(waypoint3);

//    wayPoint * waypoint4=new wayPoint(QPoint(388,222));
    wayPoint * waypoint4=new wayPoint(QPoint(388*2,222*2));
    waypoint3->setNextWayPoint(waypoint4);
    m_wayPointList.push_back(waypoint4);

//    wayPoint * waypoint5=new wayPoint(QPoint(248,222));
    wayPoint * waypoint5=new wayPoint(QPoint(248*2,222*2));
    waypoint4->setNextWayPoint(waypoint5);
    m_wayPointList.push_back(waypoint5);

//    wayPoint * waypoint6=new wayPoint(QPoint(248,151));
    wayPoint * waypoint6=new wayPoint(QPoint(248*2,151*2));
    waypoint5->setNextWayPoint(waypoint6);
    m_wayPointList.push_back(waypoint6);

//    wayPoint * waypoint7=new wayPoint(QPoint(481,151));
    wayPoint * waypoint7=new wayPoint(QPoint(481*2,151*2));
    waypoint6->setNextWayPoint(waypoint7);
    m_wayPointList.push_back(waypoint7);

//    wayPoint * waypoint8=new wayPoint(QPoint(481,223));
    wayPoint * waypoint8=new wayPoint(QPoint(481*2,223*2));
    waypoint7->setNextWayPoint(waypoint8);
    m_wayPointList.push_back(waypoint8);

//    wayPoint * waypoint9=new wayPoint(QPoint(598,223));
    wayPoint * waypoint9=new wayPoint(QPoint(598*2,223*2));
    waypoint8->setNextWayPoint(waypoint9);
    m_wayPointList.push_back(waypoint9);

//    wayPoint * waypoint10=new wayPoint(QPoint(598,149));
    wayPoint * waypoint10=new wayPoint(QPoint(598*2,149*2));
    waypoint9->setNextWayPoint(waypoint10);
    m_wayPointList.push_back(waypoint10);
}
void MainWindow::loadTowerPosition3()
{
    QPoint pos[]=
    {
        QPoint(50,700),
        QPoint(75,180),
        QPoint(50,310),
        QPoint(635,310),
        QPoint(130,260),
        QPoint(245,260),
        QPoint(245,140),
        QPoint(450,140),
        QPoint(450,240),
        QPoint(600,167),
        QPoint(550,240),
    };
    int len=sizeof(pos)/sizeof(pos[0]);
    qDebug()<<len<<endl;
    for(int i=0;i<len;i++)
    {
        m_towerPositionList.push_back(pos[i]);
    }

}

void MainWindow::addWayPoint3()
{
    wayPoint * waypoint1=new wayPoint(QPoint(2,236));
    m_wayPointList.push_back(waypoint1);

    wayPoint * waypoint2=new wayPoint(QPoint(105,236));
    m_wayPointList.push_back(waypoint2);
    waypoint1->setNextWayPoint(waypoint2);

    wayPoint * waypoint3=new wayPoint(QPoint(105,360));
    m_wayPointList.push_back(waypoint3);
    waypoint2->setNextWayPoint(waypoint3);

    wayPoint * waypoint4=new wayPoint(QPoint(292,360));
    m_wayPointList.push_back(waypoint4);
    waypoint3->setNextWayPoint(waypoint4);

    wayPoint * waypoint5=new wayPoint(QPoint(292,142));
    m_wayPointList.push_back(waypoint5);
    waypoint4->setNextWayPoint(waypoint5);

    wayPoint * waypoint6=new wayPoint(QPoint(354,142));
    m_wayPointList.push_back(waypoint6);
    waypoint5->setNextWayPoint(waypoint6);

    wayPoint * endPoint=new wayPoint(QPoint(354,100));
    m_wayPointList.push_back(endPoint);
    waypoint6->setNextWayPoint(endPoint);


    wayPoint * waypoint7=new wayPoint(QPoint(720,236));
    m_wayPointList.push_back(waypoint7);

    wayPoint * waypoint8=new wayPoint(QPoint(610,236));
    m_wayPointList.push_back(waypoint8);
    waypoint7->setNextWayPoint(waypoint8);

    wayPoint * waypoint9=new wayPoint(QPoint(610,360));
    m_wayPointList.push_back(waypoint9);
    waypoint8->setNextWayPoint(waypoint9);

    wayPoint * waypoint10=new wayPoint(QPoint(420,360));
    m_wayPointList.push_back(waypoint10);
    waypoint9->setNextWayPoint(waypoint10);

    wayPoint * waypoint11=new wayPoint(QPoint(420,142));
    m_wayPointList.push_back(waypoint11);
    waypoint10->setNextWayPoint(waypoint11);

    waypoint11->setNextWayPoint(waypoint6);
}

bool MainWindow::canBuyTower1()
{
    if(m_playerGlod>=tower1Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canBuyTower2()
{
    if(m_playerGlod>=tower2Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canBuyTower3()
{
    if(m_playerGlod>=tower3Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate1()
{
    if(m_playerGlod>=towerupdate1Cost)
    {
        return true;
    }
    return false;
}

bool MainWindow::canUpdate2()
{
    if(m_playerGlod>=towerupdate2Cost)
    {
        return true;
    }
    return false;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();
    auto it=m_towerPositionList.begin();
    while(it!=m_towerPositionList.end())
    {
        if(Qt::LeftButton==event->button())//如果是鼠标左键点击
        {//左键点击的情况下，可以实现防御塔选择button的出现和防御塔的选择,或者是在有button2的情况下，进行升级或移除的操作
            if(it->containPoint(pressPos) && !it->hasButton() && !it->hasTower() && !it->hasButton2())//在没有按钮的情况下点击，会出现button1
            {
                QPoint tmp(it->getPos().x()-35,it->getPos().y()-35);//向左上角移动35 35，得到选择框的端点
                selectButton * button=new selectButton(tmp,this);//构造一个选择框
                m_selectButtonList.push_back(button);//类似防御塔的放置，把这个button放到MainWindow的一个list中
                it->setButton(button);//设置这个防御塔坑处的button
                it->setHasButton(true);//这个坑有了button
                update();//更新mainwindow，主要是更新paintevent
                break;
            }

            else if(it->hasButton2() && it->getButton2()->containPos(pressPos) && !it->hasButton() && !it->containPoint(pressPos) &&it->hasTower())
            {//在有button2的情况下，点击button2的内部
                if(pressPos.y()<(it->getButton2()->getPos().y()+25))
                {//对防御塔进行升级
                    if(canUpdate1() && !it->hasUpdate1() && it->hasTower())
                    {
                        it->setHasUpdate1(true);
                        m_playerGlod-=towerupdate1Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamgae()+10);
                        it->get_tower()->levelChange();
                        //update();
                    }
                    else if(canUpdate2() && it->hasUpdate1() && !it->hasUpdate2())
                    {
                        it->setHasUpdate2(true);
                        m_playerGlod-=towerupdate2Cost;
                        it->get_tower()->reSetDamage(it->get_tower()->getDamgae()+20);
                        it->get_tower()->levelChange();
                        //update();
                    }
                }
                else if(pressPos.y()>it->getButton2()->getPos().y()+25)
                {//对防御塔进行移除
                    awardGlod();//移除防御塔奖励200
                    it->get_tower()->getRemoved();
                    it->setRemoveTower();
                }
                //点击了button2的内部，button2就要被移除
                it->getButton2()->getRemoved();
                it->setButton2(NULL);
                it->setHasButton2(false);
                update();
                break;
            }
            else if(it->hasButton() && !it->hasTower() && it->getButton()->containPos(pressPos))//在有button的情况下，选择三种炮台.其实这里代码有点重复了。如果用继承的方法，那就应该不要这么多的重复代码
            {
                if(pressPos.x()<it->getButton()->getPos().x()+35)//鼠标点在选择框中的第一个防御塔内
                {
                    if(canBuyTower1())
                    {
                        it->setHasTower1(true);
                        m_playerGlod-=tower1Cost;
                        QString path=":/images/tower0.png";
                        Tower * tower=new Tower(it->centerPos(),this,path,10);//四个参数，分别是防御塔的中心点；主界面；防御塔图片路径；防御塔的攻击力
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();

                    }
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+35 && pressPos.x()<it->getButton()->getPos().x()+70)//鼠标点在第二个防御塔的图片中
                {
                    if(canBuyTower2())
                    {
                        it->setHasTower2(true);
                        m_playerGlod-=tower2Cost;
                        QString path=":/images/tower2.png";
                        Tower * tower=new Tower(it->centerPos(),this,path,15);
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();
                    }
                }
                else if(pressPos.x()>it->getButton()->getPos().x()+70 && pressPos.x()<it->getButton()->getPos().x()+105)//第三个图片
                {
                    if(canBuyTower3())
                    {
                        it->setHasTower3(true);
                        m_playerGlod-=tower3Cost;
                        QString path=":/images/tower3.png";
                        Tower * tower=new Tower(it->centerPos(),this,path,20);
                        it->setTower(tower);
                        m_towerList.push_back(tower);
                        update();
                    }
                }

                it->getButton()->getRemoved();
                it->setButton(NULL);
                it->setHasButton(false);
                update();
                break;
            }
        }
        else if(Qt::RightButton==event->button())//如果是鼠标右键点击
        {//在有防御塔的情况下，右键会出现选择框，升级还有移除
            if(it->containPoint(pressPos) && (!it->hasButton2()) && it->hasTower())
            {
                it->setHasButton2(true);
                QPoint tmp(it->getPos().x()+35,it->getPos().y());
                selectButton2 * button2=new selectButton2(tmp,this,100,50);
                button2->setTower(it->get_tower());
                m_selectButton2List.push_back(button2);
                it->setButton2(button2);
                update();
                break;
            }
        }
        ++it;
    }
}

void MainWindow::setPath(QString path)
{
    m_path=path;
}

QString MainWindow::getPath()
{
    return m_path;
}

void MainWindow::getHpDamage()
{
    m_playerHp-=1;
    if(m_playerHp<=0)
    {
        doGameOver();
    }
}

void MainWindow::doGameOver()
{
    if(!m_gameEnd)
    {
        m_gameEnd=true;
    }
}

void MainWindow::removeTower(Tower * tower)
{
    Q_ASSERT(tower);
    m_towerList.removeOne(tower);
    delete tower;
}

void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_score+=enemy->getm_ScoreAD();
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        ++m_waves;
        if(!loadWaves())
        {
            m_gameWin=true;
        }
    }
}

void MainWindow::removeButton(selectButton *button)
{
    Q_ASSERT(button);
    m_selectButtonList.removeOne(button);
    delete button;
}

void MainWindow::removeButton2(selectButton2 *button)
{
    Q_ASSERT(button);
    m_selectButton2List.removeOne(button);
    delete button;
}

bool MainWindow::loadWaves()
{
    if(m_waves>=6)
    {
        return false;
    }

    int enemyStartInterval[]={100,500,600,1000,3000,6000};
    for(int i=0;i<6;++i)
    {
        wayPoint * startWayPoint;
        if(getPath()==":/images/background4.jpg")
        {
            int a=rand()%100;
            if(a<50)
            {
                startWayPoint=m_wayPointList.first();
            }
            if(a>=50)
            {
               startWayPoint=m_wayPointList[7];
            }
        }
        else
        {
            startWayPoint=m_wayPointList.first();
        }
        Enemy * enemy=new Enemy(startWayPoint,this);

        m_enemyList.push_back(enemy);
        enemy->reSetHp(40+20*(0+m_waves));
        QTimer::singleShot(enemyStartInterval[i],enemy,SLOT(doActive()));
    }
    return true;
}

QList<Enemy *> MainWindow::getEnemyList()
{
    return m_enemyList;
}

void MainWindow::removeBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void MainWindow::setTitle(int n)
{
    this->setWindowTitle(QString("第%1关").arg(n));
}

void MainWindow::playmusic()
{
//    QSound* sound=new QSound(":/img/images/back_mus.wav",this);
//    sound->setLoops(-1);
//    sound->s
//    sound->play();

        sound=new QMediaPlayer(this);
        sound->setMedia(QUrl("qrc:/img/images/back_mus.wav"));
        sound->setVolume(50);
        sound->play();
//        sound->stop();
}

void MainWindow::awardGlod()
{
    m_playerGlod+=200;
    update();
}

void MainWindow::drawWaves(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::black);
    QFont font("宋体",10,QFont::Bold,true);
    painter->setFont(font);
    painter->drawText(QRect(500,5,100,25),QString("WAVES: %1").arg(m_waves+1));
    painter->restore();
}

void MainWindow::drawHp(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::black);
    QFont font("宋体",10,QFont::Bold,true);
    painter->setFont(font);
    painter->drawText(QRect(30,5,100,25),QString("HP: %1").arg(m_playerHp));
    painter->restore();
}

void MainWindow::drawGlod(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::black);
    QFont font("宋体",10,QFont::Bold,true);
    painter->setFont(font);
    painter->drawText(QRect(300,5,200,25),QString("GLOD: %1").arg(m_playerGlod));
    painter->restore();
}
