#include "objectivefunction.h"
#include <stdexcept>
#include <cmath>


std::size_t ObjectiveFunction::size() const
{
    return _size;
}
int ObjectiveFunction::at(std::size_t i, std::size_t j) const
{
    i--; j--;
    if(i >= _size && j >= _size)
        throw std::out_of_range("ObjectiveFunction::at(): out of range");

    return _weightMatrix.at(i * _size + j);
}

ObjectiveFunction::ObjectiveFunction(std::vector<int> &&weightMatrix):
    _size(sqrt(weightMatrix.size())), _weightMatrix(weightMatrix)
{
    if(_size * _size != weightMatrix.size())
        throw std::invalid_argument("ObjectiveFunction::ObjectiveFunction() invalid argument weightMatrix");
}

ObjectiveFunction::ObjectiveFunction(const std::vector<int> &weightMatrix):
    _size(sqrt(weightMatrix.size())), _weightMatrix(weightMatrix)
{
    if(_size * _size != weightMatrix.size())
        throw std::invalid_argument("ObjectiveFunction::ObjectiveFunction() invalid argument weightMatrix");
}

int ObjectiveFunction::operator()(const Substitution &sub)
{
    if(sub.size() != _size)
        throw std::invalid_argument("ObjectiveFunction::operator(): not equal size");
    int result = 0;
    int lastElement = sub.size() - 1;
    for(int i = 0; i < lastElement; i++)
    {
        result += at(sub[i], sub[i + 1]);
    }
    result += at(sub[lastElement], sub[0]);
    return result;
}
