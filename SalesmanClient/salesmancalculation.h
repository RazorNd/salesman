#ifndef SALESMANCALCULATION_H
#define SALESMANCALCULATION_H

#include "salesman.h"
#include <QThread>
#include <vector>

class SalesmanCalculation : public QThread
{
    Q_OBJECT
    std::vector<int> _matrixWeight;
    int _countItertion;
    int _cityCount;
    int _sizePopulation;
    int _countReprodution;
    int _countMutation;

    void setCityCount();
public:
    explicit SalesmanCalculation(QObject *parent = 0);

    int countItertion() const;
    int sizePopulation() const;
    int countReprodution() const;
    int countMutation() const;
    int cityCount() const;

    void setMatrixWeight(const std::vector<int> matrixWeight);

public slots:
    void setCountItertion(int countItertion);
    void setSizePopulation(int sizePopulation);
    void setCountReprodution(int countReprodution);
    void setCountMutation(int countMutation);

signals:
    void countItertionChanged(int countItertion);
    void calculationProgress(int val);
    void calculationProgress(QString res);
    void calculationResult(QString res);
    // QThread interface
protected:
    void run();
};

#endif // SALESMANCALCULATION_H
