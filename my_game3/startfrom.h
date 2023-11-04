#ifndef STARTFROM_H
#define STARTFROM_H

#include "mainwindow.h"



namespace Ui {
class StartFrom;
}

class StartFrom : public QWidget
{
    Q_OBJECT

public:
    explicit StartFrom(QWidget *parent = nullptr,QString username="");
    ~StartFrom();
    void paintEvent(QPaintEvent *);
    QString m_username;
private slots:
//    void on_PList_but_clicked();

private:
    Ui::StartFrom *ui;
};

#endif // STARTFROM_H
