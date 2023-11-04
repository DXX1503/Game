#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"
#include "CMySql.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QtDebug>
#include <QStringList>
class MainWindow;


StartFrom::StartFrom(QWidget *parent,QString username):
    QWidget(parent),
    m_username(username),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);
    setWindowTitle("作者都不知道该如何称呼这款作品");
    ui->pushButton->setStyleSheet("background-color:green");
    ui->pushButton_2->setStyleSheet("background-color:green");
    ui->pushButton_3->setStyleSheet("background-color:green");
    //打开第一关
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        this->hide();
        MainWindow * mainwindow=new MainWindow(parent,username);
        mainwindow->setPath(":/images/background1.jpg");
        mainwindow->setTitle(1);
        mainwindow->loadTowerPosition1();
        mainwindow->addWayPoint1();
        mainwindow->show();
    });
    //打开第二关
    connect(ui->pushButton_2,&QPushButton::clicked,[=]()
    {
        this->hide();
        MainWindow * mainwindow=new MainWindow(parent,username);
        mainwindow->setPath(":/images/background2.jpg");
        mainwindow->setTitle(2);
        mainwindow->loadTowerPosition2();
        mainwindow->addWayPoint2();
        mainwindow->show();
    });
    //打开第三关
    connect(ui->pushButton_3,&QPushButton::clicked,[=]()
    {
        this->hide();
        MainWindow * mainwindow=new MainWindow(parent,username);
        mainwindow->setPath(":/images/background4.jpg");
        mainwindow->setTitle(3);
        mainwindow->loadTowerPosition3();
        mainwindow->addWayPoint3();
        mainwindow->show();
    });

    //查看积分榜功能
    connect(ui->PList_but,&QPushButton::clicked,[=](){
        QTableWidget* p=new QTableWidget(nullptr);
        p->setFixedSize(this->width(),this->height());
        QStringList strList{"用户名","积分"};
        p->setColumnCount(strList.size());
        p->setHorizontalHeaderLabels(strList);
        CMySql conn("utf8");
        char peer[MAX_ERR_LEN]={0};
        if(!conn.ConnectMySql("localhost","root","142986","test",3306,peer))
        {
            QMessageBox::critical(nullptr,"error",QString("error: ")+peer);
            return;
        }


        //p.show();
        QString sql1="select name,scoer from TF_user where name= '"+m_username+"';";
        qDebug()<<sql1<<endl;
        qDebug()<<m_username<<endl;
        vector<vector<string>> res;
        if(conn.SelectMySql(sql1.toStdString().c_str(),res,peer))
        {
            qDebug()<<res.size()<<endl;
            qDebug()<<res[0].size()<<endl;
            p->setRowCount(res.size());
            for(unsigned long long i=0;i<res.size();i++)
            {
                for(unsigned long long j=0;j<res[i].size();j++)
                {
                    qDebug()<<res[i][j].c_str()<<endl;
                }
            }

            for(unsigned long long i=0;i<res.size();i++)
            {
                for(unsigned long long j=0;j<res[i].size();j++)
                {
                    QTableWidgetItem * pitm=new QTableWidgetItem;
                    pitm->setText(res[i][j].c_str());
                    p->setItem(i,j,pitm);
                }
            }


        }
        else
        {
            QMessageBox::critical(nullptr,"error","sb");
        }

        p->show();
        conn.DisConnect();

    });
}

void StartFrom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap mP(":/images/background.jpg");
    mP=mP.scaled(this->width(),this->height(),Qt::IgnoreAspectRatio,Qt::FastTransformation);
    painter.drawPixmap(0,0,mP.width(),mP.height(),mP);
}

StartFrom::~StartFrom()
{
    delete ui;
}

//void StartFrom::on_PList_but_clicked()
//{
//    CMySql conn("utf8");
//    char peer[MAX_ERR_LEN]={0};
//    if(!conn.ConnectMySql("localhost","root","142986","test",3306,peer))
//    {
//        QMessageBox::critical(nullptr,"error",QString("error: ")+peer);
//        return;
//    }
//    QTableWidget* p=new QTableWidget(nullptr);
//    //p.show();
//    QString sql1="select name,scoer from TF_user where name= '"+m_username+"';";
//    vector<vector<string>> res;
//    if(conn.SelectMySql(sql1.toStdString().c_str(),res,peer))
//    {
//        for(int i=0;i<res.size();i++)
//        {
//            for(int j=0;j<res[0].size();j++)
//            {
//                QTableWidgetItem * pitm=new QTableWidgetItem;
//                pitm->setText(res[i][j].c_str());
//                p->setItem(i,j,pitm);
//            }
//        }


//    }

//}

