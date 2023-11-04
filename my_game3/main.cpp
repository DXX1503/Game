#include "startfrom.h"
#include "mainwindow.h"
#include <QApplication>
#include "reallystartform.h"
#include "form.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ReallyStartForm w;
    Form p;
    p.show();
//    w.show();
    return a.exec();
}
