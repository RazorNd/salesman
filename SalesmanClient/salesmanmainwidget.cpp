#include "salesmanmainwidget.h"
#include "ui_salesmanmainwidget.h"
#include <QMimeData>
#include <QDebug>
#include <QMessageBox>

SalesmanMainWidget::SalesmanMainWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SalesmanMainWidget)
{
    ui->setupUi(this);
    model = new SalesmanWeightMatrixModel(5, this);

    calculatingEngine = new SalesmanCalculation(this);

    ui->view->setModel(model);
    connect(model, SIGNAL(sizeChanged(int)),
            ui->sizeMatrixWeight, SLOT(setValue(int)));
    connect(ui->sizeMatrixWeight, SIGNAL(valueChanged(int)),
            model, SLOT(setSize(int)));
    connect(ui->sizePopulation, SIGNAL(valueChanged(int)), SLOT(changeMaxPopulation(int)));
    connect(ui->sizePopulation, SIGNAL(valueChanged(int)),
            calculatingEngine, SLOT(setSizePopulation(int)));
    connect(ui->countReproduction, SIGNAL(valueChanged(int)),
            calculatingEngine, SLOT(setCountReprodution(int)));
    connect(ui->countMutation, SIGNAL(valueChanged(int)),
            calculatingEngine, SLOT(setCountMutation(int)));
    connect(ui->countIterationCalc, SIGNAL(valueChanged(int)),
            calculatingEngine, SLOT(setCountItertion(int)));
    connect(calculatingEngine, SIGNAL(calculationProgress(int)),
            ui->progressBarCalculation, SLOT(setValue(int)));
    connect(calculatingEngine, SIGNAL(countItertionChanged(int)),
            ui->progressBarCalculation, SLOT(setMaximum(int)));
    connect(calculatingEngine, SIGNAL(started()),
            ui->progressBarCalculation, SLOT(reset()));
    connect(calculatingEngine, SIGNAL(calculationProgress(QString)),
            ui->logCalculation, SLOT(appendPlainText(QString)));
    connect(calculatingEngine, SIGNAL(calculationResult(QString)),
            ui->logCalculation, SLOT(appendPlainText(QString)));
    connect(ui->beginCalculation, SIGNAL(clicked()),
            SLOT(calculatingStart()));

    ui->sizePopulation->setValue(10);
    ui->countReproduction->setValue(5);
    ui->countMutation->setValue(3);
    ui->countIterationCalc->setValue(20);
}

SalesmanMainWidget::~SalesmanMainWidget()
{
    delete ui;
}

void SalesmanMainWidget::changeMaxPopulation(int val)
{
    ui->countReproduction->setMaximum(val);
    ui->countMutation->setMaximum(val);
}

void SalesmanMainWidget::calculatingStart()
{
    calculatingEngine->setMatrixWeight(model->getMatrixWeight());
    calculatingEngine->start();
}

void SalesmanMainWidget::paste()
{
    const QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    model->dropMimeData(mimeData, Qt::CopyAction, -1, -1, QModelIndex());
}

void SalesmanMainWidget::aboutProgram()
{
    QMessageBox::about(this, "Эволюционные вычисления",
                       "<html>\
                       <head>\
                       <style>\
                       .leftimg {\
                           width: 200px;\
                           float:left;	\
                       }\
                       .text {\
                           margin-left: 207px;\
                       }\
                       </style>\
                       </head>\
                       <body>\
                           <div>\
                               <h3>Эволюционные вычисления</h3>\
                               <p>Данная программа создана для выполнения лабораторной работы по предмету Представление знаний в ИС, для решения задачи коммивояжёра</p>	\
                               </div>	\
                               <center><b>&copy;2015</b> Программу разработал Разоренов Д.А.</center>\
                       </body>\
                       </html>");
}
