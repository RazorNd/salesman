#include "substitution.h"
#include <set>
#include <list>
#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <sstream>

ObjectiveFunction Substitution::_funtion = ObjectiveFunction(std::vector<int>());

ObjectiveFunction Substitution::getFuntion()
{
    return _funtion;
}

void Substitution::setFuntion(const ObjectiveFunction &value)
{
    _funtion = value;
}
void Substitution::randomInit()
{
    std::set<int> exists;
    for(std::vector<int>::iterator it = _data.begin();
        it != _data.end(); it++)
    {
        int randomNumber;
        bool isExistsNumber;
        do
        {
            randomNumber = rand() % _size + 1;
            std::pair<std::set<int>::iterator, bool> resultInsert
                    = exists.insert(randomNumber);
            isExistsNumber = !resultInsert.second;
        }while(isExistsNumber);
        *it = randomNumber;
    }
}

bool Substitution::isCorrect()
{
    std::set<int> exists;
    for(std::vector<int>::const_iterator it = _data.begin();
        it != _data.end(); it++)
    {
        std::pair<std::set<int>::iterator, bool> result = exists.insert(*it);
        if(!result.second)
        {
            return false;
        }
    }

    int i = 1;
    for(std::set<int>::const_iterator it = exists.begin();
        it != exists.end(); it++)
    {
        if(*it != i)
        {
            return false;
        }
        i++;
    }

    return true;
}

Substitution::Substitution(std::size_t size):
    _size(size), _data(size)
{
    randomInit();
}

Substitution::Substitution(std::vector<int> &data):
    _size(data.size()), _data(data)
{
    if(!isCorrect())
        throw std::logic_error("Substitution::Substitution(): param 'data' is not correct");
}

std::size_t Substitution::size() const
{
    return _size;
}

std::string Substitution::toString() const
{
    std::stringstream out;
    out << *this;
    return out.str();
}

int Substitution::operator[](std::size_t i) const
{
    return _data.at(i);
}

bool Substitution::operator <(const Substitution &other) const
{
    return getFuntion()(*this) < getFuntion()(other);
}

Substitution Substitution::operator*(const Substitution &other) const
{
    if(other.size() != _size)
        throw std::logic_error("Substitution::operator*: not equal size");

    std::vector<int> result(_size);
    for(std::size_t i = 0; i < _size; i++)
    {
        result[i] = _data[other[i] - 1];
    }    
    return Substitution(result);
}

Substitution Substitution::mutate(std::size_t pos) const
{
    if(pos + 1 >= _size)
        throw std::out_of_range("Substitution::mutate: pos out of range");

    std::vector<int> result = _data;
    std::swap(result[pos], result[pos + 1]);    
    return Substitution(result);
}

std::ostream &operator <<(std::ostream &out, const Substitution &substitution)
{
    out << "(";
    std::size_t lastElementIndex = substitution.size() - 1;
    for(std::size_t i = 0; i < lastElementIndex; i++)
    {
        out << substitution[i] << ", ";
    }
    return out << substitution[lastElementIndex] << ")";

}
