#include "salesmanmainwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SalesmanMainWidget w;
    w.showNormal();
    return a.exec();
}
