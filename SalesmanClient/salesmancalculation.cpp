#include "salesmancalculation.h"
#include <QtMath>
#include <QTextStream>

int SalesmanCalculation::countItertion() const
{
    return _countItertion;
}

void SalesmanCalculation::setCountItertion(int countItertion)
{
    _countItertion = countItertion;    
}

int SalesmanCalculation::sizePopulation() const
{
    return _sizePopulation;
}

void SalesmanCalculation::setSizePopulation(int sizePopulation)
{
    _sizePopulation = sizePopulation;
}

int SalesmanCalculation::countReprodution() const
{
    return _countReprodution;
}

void SalesmanCalculation::setCountReprodution(int countReprodution)
{
    _countReprodution = countReprodution;
}

int SalesmanCalculation::countMutation() const
{
    return _countMutation;
}

void SalesmanCalculation::setCountMutation(int countMutation)
{
    _countMutation = countMutation;
}

int SalesmanCalculation::cityCount() const
{
    return _cityCount;
}

void SalesmanCalculation::setMatrixWeight(const std::vector<int> matrixWeight)
{
    _matrixWeight = matrixWeight;
    setCityCount();
}

void SalesmanCalculation::setCityCount()
{
    _cityCount = qSqrt(_matrixWeight.size());
}

SalesmanCalculation::SalesmanCalculation(QObject *parent) :
    QThread(parent)
{
}


void SalesmanCalculation::run()
{
    Substitution::setFuntion(ObjectiveFunction(_matrixWeight));
    Salesman engine(_cityCount, _sizePopulation);
    engine.setReproductionCount(_countReprodution);
    engine.setMutationsCount(_countMutation);

    emit countItertionChanged(_countItertion);
    for(int i = 0; i < _countItertion; i++)
    {
        emit calculationProgress(i);
        emit calculationProgress(QString("Номер шага: %1, лучший результат: %2, средний результат: %3")
                                 .arg(i + 1)
                                 .arg(engine.makeStep())
                                 .arg(engine.averageResult()));
    }
    emit calculationProgress(_countItertion);
    emit calculationResult(QString("Ответ: %1")
                           .arg(QString::fromStdString(engine.answer().toString())));
}
