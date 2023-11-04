#include "form.h"
#include "ui_form.h"
#include "reallystartform.h"
#include "mainwindow.h"

#include  <QString>
#include  <QVector>
#include <QMessageBox>
#include <vector>
#include <string>
#include <QDebug>
#include <iostream>
#include <QEvent>



Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),
    m_mysql("utf8")
//    m_p(nullptr)
{
//    this->hide();
//    m_p->show();
    ui->setupUi(this);
    //连接失败，接收错误信息
    char peer[MAX_ERR_LEN]={0};
    if(!m_mysql.ConnectMySql("localhost","root","142986","test",3306,peer))
    {
        QMessageBox::critical(nullptr,"error",QString("aaa")+peer);
        return;
    }
    ui->UserPawd_txt->setEchoMode(QLineEdit::Password);
    connect(ui->regist_button,SIGNAL(clicked()),this,SLOT(on_regist_button_clicked()));
//    connect(ui->login_button,SIGNAL(clicked()),this,SLOT(on_login_button_clicked()));

    connect(ui->login_button,&QPushButton::clicked,[=](){
        QString name=ui->UserName_txt->text();
        QString passwd=ui->UserPawd_txt->text();
        QString sql1="select passwd from TF_user where name= '"+name+"';";
        qDebug()<<sql1<<endl;
        vector<vector<string>> res;
        char perr[MAX_ERR_LEN]={0};
        if(!m_mysql.SelectMySql(sql1.toStdString().c_str(),res,perr))
        {
           QMessageBox::critical(nullptr,"error",QString("所填信息错误")+perr);
           return;
        }
        int colum=res.size();
        int hcolm=res[0].size();
        for(int i=0;i<colum;i++)
        {
            for(int j=0;j<hcolm;j++)
            {
                cout<<res[i][j]<<endl;
            }
        }
        if(res[0][0]==passwd.toStdString())
        {
        }
        else
        {
            QMessageBox::critical(nullptr,"error",QString("所填信息错误")+perr);
            return;
        }
        qDebug()<<"hello world"<<endl;
        m_username=ui->UserName_txt->text();
        this->hide();
        ReallyStartForm *p=new ReallyStartForm(parent,m_username);
        p->show();
        m_mysql.DisConnect();
    });
}

Form::~Form()
{
//    if(!m_p)
//    {
//        delete  m_p;
//    }
//    m_p=nullptr;
    delete ui;
}

void Form::on_regist_button_clicked()
{
    QString name=ui->UserName_txt->text();
    QString passwd=ui->UserPawd_txt->text();
    qDebug()<<name<<endl;
    qDebug()<<passwd<<endl;
    QString sql1="insert into TF_user(name,passwd) values('"+name+"',"+passwd+");";
    qDebug()<<sql1<<endl;
    if(m_mysql.UpdateMySql((char *)sql1.toStdString().c_str()))
    {
        QMessageBox::information(this,"regist","注册成功");
        return;
    }
    else
    {
        QMessageBox::critical(this,"error","请检查信息或者重复注册");
        return;
    }
}

void Form::on_login_button_clicked()
{
    QString name=ui->UserName_txt->text();
    QString passwd=ui->UserPawd_txt->text();
    QString sql1="select passwd from TF_user where name= '"+name+"';";
    qDebug()<<sql1<<endl;
    vector<vector<string>> res;
    char perr[MAX_ERR_LEN]={0};
    if(!m_mysql.SelectMySql(sql1.toStdString().c_str(),res,perr))
    {
       QMessageBox::critical(nullptr,"error",QString("所填信息错误")+perr);
       return;
    }
    int colum=res.size();
    int hcolm=res[0].size();
    for(int i=0;i<colum;i++)
    {
        for(int j=0;j<hcolm;j++)
        {
            cout<<res[i][j]<<endl;
        }
    }
    if(res[0][0]==passwd.toStdString())
    {
    }
    else
    {
        QMessageBox::critical(nullptr,"error",QString("所填信息错误")+perr);
        return;
    }
//    this->hide();
//    w=new ReallyStartForm(this);
//    w->show();

//    p.show();
//    this->hide();

//    m_p->show();
    //    this->hide();
}

//void Form::keyPressEvent(QKeyEvent *event)
//{
//    QString m_tel;
//    qDebug()<<"按下的键为 "<<event->key();
//    if(event->key()== Qt::Key_Backspace){

//    m_tel = m_tel.left(m_tel.size()-1);   //左边截取n-1 位
//    ui->UserPawd_txt->setText(ui->UserPawd_txt->text().left(ui->UserPawd_txt->text().size()-1));
//    //this->setText(this->text().left(this->text().size()-1));
//    }

//    else if(m_tel.size()<11)
//    {
//    m_tel+=QString::number(event->key()-Qt::Key_0);
//    if(m_tel.size()<=3){
//        this->setText(m_tel);
//        ui->UserPawd_txt->setText(m_tel);

//    }else if(3<m_tel.size()&&m_tel.size()<=7 ){
//        QString tel = m_tel.left(3);
//        for( int i=3;i< m_tel.size();i++ ){
//            tel+="*";
//        }
//        this->setText(tel);
//        ui->UserPawd_txt->setText(m_tel);
//    }else{
//        QString tel = m_tel.left(3)+"****"+m_tel.right(m_tel.size()-7);
//      this->setText(tel);
//        ui->UserPawd_txt->setText(tel);
//    }
//    }

//}

//bool Form::event(QEvent * ev)
//{
//    if(ev->type()==QEvent::KeyPress)
//    {
//        QKeyEvent *pkey=(QKeyEvent *)ev;
//        if((Qt::Key_0<=pkey->key()&&Qt::Key_9>=pkey->key())||pkey->key()==Qt::Key_Backspace)//按键符合要求，调用父类事件分发正常处理
//        {
//           return ui->UserPawd_txt->event(ev);

//        }
//        else
//        {
//            qDebug()<<"输入信息不符合要求 "<<pkey->key();
//            return true;//表示该事件已经被处理，不用理会
//        }
//    }

//    return ui->UserPawd_txt->event(ev);
//}

