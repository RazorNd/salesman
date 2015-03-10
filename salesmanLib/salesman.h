#ifndef SALESMAN_H
#define SALESMAN_H

#include "substitution.h"
#include <set>
#include <functional>

class Salesman
{
    static std::default_random_engine random;

    const std::size_t _cityCount;
    std::size_t _populationSize;
    std::multiset<Substitution> _population;
    std::size_t _reproductionCount;

    Substitution createNew() const;
    void addForScarceTravels();
    void deleteForScarceTravels();
    void reproduction(int count);
    Substitution reproduction(const Substitution& a, const Substitution& b) const;
public:
    const Substitution &at(std::size_t i) const;

    Salesman(std::size_t cityCount, std::size_t populationSize);
    std::size_t populationSize() const;
    void setPopulationSize(std::size_t populationSize);
    std::size_t cityCount() const;    
    std::size_t reproductionCount() const;
    void setReproductionCount(const std::size_t &value);

    int bestSolution() const;
    int makeStep();
    Substitution answer() const;
};

#endif // SALESMAN_H
