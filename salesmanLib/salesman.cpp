#include "salesman.h"
#include <random>
#include <ctime>

std::default_random_engine Salesman::random(time(0));

std::size_t Salesman::populationSize() const
{
    return _populationSize;
}

void Salesman::setPopulationSize(std::size_t populationSize)
{
    _populationSize = populationSize;
}

std::size_t Salesman::cityCount() const
{
    return _cityCount;
}


std::size_t Salesman::reproductionCount() const
{
    return _reproductionCount;
}

void Salesman::setReproductionCount(const std::size_t &value)
{
    _reproductionCount = value;
}

int Salesman::bestSolution() const
{
    return Substitution::getFuntion()(*(_population.begin()));
}

double Salesman::averageResult() const
{
    int sum = 0;
    for(auto &a: _population)
    {
        sum += Substitution::getFuntion()(a);
    }
    return (double)sum / _populationSize;
}

int Salesman::makeStep()
{
    mutate(_mutationsCount);
    reproduction(_reproductionCount);
    deleteForScarceTravels();
    return bestSolution();
}

Substitution Salesman::answer() const
{
    return *(_population.begin());
}


std::size_t Salesman::mutationsCount() const
{
    return _mutationsCount;
}

void Salesman::setMutationsCount(const std::size_t &mutationsCount)
{
    _mutationsCount = mutationsCount;
}
Substitution Salesman::createNew() const
{
    return Substitution(_cityCount);
}

void Salesman::addForScarceTravels()
{
    int div = _populationSize - _population.size();
    for(int i  = 0; i < div; i++)
    {
        _population.insert(createNew());
    }
}

void Salesman::deleteForScarceTravels()
{
    int div = _population.size() - _populationSize;

    auto it = _population.end();
    for(int i = 0; i < div; i++)
        it--;
    _population.erase(it, _population.end());
}

void Salesman::reproduction(int count)
{
    for(int i = 0; i < count; i++)
    {
        _population.insert(reproduction(at(random()%_populationSize),
                                        at(random()%_populationSize)));
    }
}

void Salesman::mutate(int count)
{
    for(int i = 0; i < count; i++)
    {
        _population.insert(mutate(at(random()%_populationSize)));
    }
}

Substitution Salesman::mutate(const Substitution &a) const
{
    return a.mutate(random()%(_cityCount - 1));
}

Substitution Salesman::reproduction(const Substitution &a, const Substitution &b) const
{
    return a * b;
}

const Substitution &Salesman::at(std::size_t i) const
{
    auto it = _population.cbegin();
    for(std::size_t a = 0; a < i; a++)
    {
        it++;
    }
    return *it;
}

Salesman::Salesman(std::size_t cityCount, std::size_t populationSize):
    _cityCount(cityCount),
    _populationSize(populationSize),
    _reproductionCount(populationSize/2),
    _mutationsCount(populationSize/2)
{
    addForScarceTravels();
}
