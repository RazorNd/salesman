#ifndef SALESMANMAINWIDGET_H
#define SALESMANMAINWIDGET_H

#include "salesmanweightmatrixmodel.h"
#include "salesmancalculation.h"
#include <QMainWindow>
#include <QClipboard>

namespace Ui {
class SalesmanMainWidget;
}

class SalesmanMainWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit SalesmanMainWidget(QWidget *parent = 0);
    ~SalesmanMainWidget();

private slots:
    void changeMaxPopulation(int val);
    void calculatingStart();
    void paste();
    void aboutProgram();

private:
    Ui::SalesmanMainWidget *ui;
    SalesmanWeightMatrixModel *model;
    SalesmanCalculation *calculatingEngine;
};

#endif // SALESMANMAINWIDGET_H
