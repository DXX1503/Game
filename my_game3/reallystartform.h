#ifndef REALLYSTARTFORM_H
#define REALLYSTARTFORM_H

#include <QWidget>
#include <mainwindow.h>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
namespace Ui {
class ReallyStartForm;
}

class ReallyStartForm : public QWidget
{
    Q_OBJECT

public:
    explicit ReallyStartForm(QWidget *parent = nullptr,QString username="");
    ~ReallyStartForm();
    void paintEvent(QPaintEvent *);
private:
    Ui::ReallyStartForm *ui;
public:
    QString m_username;
};

#endif // REALLYSTARTFORM_H
