#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H

#include "substitution.h"
#include <vector>

class Substitution;

class ObjectiveFunction
{
    std::size_t _size;
    std::vector<int> _weightMatrix;

    int at(std::size_t i, std::size_t j) const;
public:    
    //ObjectiveFunction(std::vector<int>&& weightMatrix);
    ObjectiveFunction(const std::vector<int>& weightMatrix);

    int operator() (const Substitution &sub);
    std::size_t size() const;
};

#endif // OBJECTIVEFUNCTION_H
