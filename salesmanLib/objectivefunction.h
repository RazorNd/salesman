#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include "substitution.h"
#include <vector>

class Substitution;

class ObjectiveFunction
{
    std::size_t _size;
    std::vector<int> _weightMatrix;
public:    
    ObjectiveFunction(std::vector<int>&& weightMatrix);

    int at(std::size_t i, std::size_t j) const;

    int operator() (const Substitution &sub);
};

#endif // OBJECTIVEFUNCTION_H
