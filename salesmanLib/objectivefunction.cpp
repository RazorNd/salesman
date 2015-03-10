#include "objectivefunction.h"
#include <stdexcept>
#include <cmath>

int ObjectiveFunction::at(std::size_t i, std::size_t j) const
{
    i--; j--;
    if(i + j >= _weightMatrix.size())
    {
        throw std::logic_error("Pizdec!!!");
    }
    return _weightMatrix.at(i * _size + j);
}

ObjectiveFunction::ObjectiveFunction(std::vector<int> &&weightMatrix):
    _size(sqrt(weightMatrix.size())), _weightMatrix(weightMatrix)
{
}

int ObjectiveFunction::operator()(const Substitution &sub)
{
    if(sub.size() != _size)
        throw std::logic_error("ObjectiveFunction::operator(): not equal size");
    int result = 0;
    int lastElement = sub.size() - 1;
    for(int i = 0; i < lastElement; i++)
    {
        result += at(sub[i], sub[i + 1]);
    }
    result += at(sub[lastElement], sub[0]);
    return result;
}
