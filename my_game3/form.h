#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QLineEdit>
#include "CMySql.h"
#include "reallystartform.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

private slots:
    void on_regist_button_clicked();
    void on_login_button_clicked();

private:
    Ui::Form *ui;
public:
    CMySql m_mysql;
public:
    QString m_username;
//    void keyPressEvent(QKeyEvent * event) override;
//    bool event(QEvent *) Q_DECL_OVERRIDE;
//    ReallyStartForm p;
//public:
//    ReallyStartForm *m_p;

};

#endif // FORM_H
