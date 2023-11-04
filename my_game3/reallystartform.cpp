#include "reallystartform.h"
#include "ui_reallystartform.h"
#include "startfrom.h"
#include "CMySql.h"

#include <QPushButton>
#include <QDebug>
ReallyStartForm::ReallyStartForm(QWidget *parent,QString username) :
    QWidget(parent),
     ui(new Ui::ReallyStartForm),
     m_username(username)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(1000,1000));
    QPushButton *msbut=new QPushButton();
    msbut->setMaximumWidth(100);
    msbut->setMinimumWidth(100);
    msbut->setMaximumHeight(50);
    msbut->setMinimumHeight(50);
    msbut->setStyleSheet("QPushButton{border-image: url(:/img/images/Enter1.jpg)}");
    msbut->move(this->width()*0.5-msbut->width()*0.5,this->height()*0.7);
    msbut->setParent(this);
    msbut->show();
    connect(msbut,&QPushButton::clicked,[=]()
    {
        this->hide();
        StartFrom * st=new StartFrom(parent,m_username);
        st->show();
        qDebug()<<"hello world"<<endl;
    });
}

ReallyStartForm::~ReallyStartForm()
{
    delete ui;
}

void ReallyStartForm::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    QString p(":/img/images/startEnum.jpg");
    paint.drawPixmap(0,0,1000,1000,p);
    //m_back=QPixmap (":/img/images/start_bu.jpg");
    //    paint.drawPixmap(mp.width()/2-m_p2.width()/2,mp.height()-m_p2.height()-50,m_p2.width(),m_p2.height(),m_p2);
    //    QPushButton m_Qp;
    //    QIcon start_but=QIcon(":/img/images/start_bu.jpg");
    //    m_Qp.setIcon(start_but);
    //    m_Qp.move(this->width()/2,this->height()/2);
    //    m_Qp.show();


}
