#include "substitution.h"
#include <set>
#include <list>
#include <stdexcept>
#include <random>
#include <ctime>
#include <sstream>

ObjectiveFunction Substitution::_funtion(std::move(std::vector<int>()));
std::default_random_engine Substitution::random(time(0));

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
    for(auto &a: _data)
    {
        int randomNumber;
        bool isExistsNumber;
        do
        {
            randomNumber = random() % _size + 1;
            auto resultInsert = exists.insert(randomNumber);
            isExistsNumber = !resultInsert.second;
        }while(isExistsNumber);
        a = randomNumber;
    }    
}

bool Substitution::isCorrect()
{
    std::set<int> exists;
    for(auto &a: _data)
    {
        auto result = exists.insert(a);
        if(!result.second)
        {
            return false;
        }
    }

    int i = 1;
    for(auto &a: exists)
    {
        if(a != i)
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

Substitution::Substitution(std::vector<int> &&data):
    _size(data.size()), _data(data)
{
    if(!isCorrect())
        throw std::logic_error("Substitution::Substitution(): param 'data' is not correct");
}

Substitution::Substitution(std::initializer_list<int> &&initList):
    _size(initList.size()), _data(initList)
{
    if(!isCorrect())
        throw std::logic_error("Substitution::Substitution(): param 'initList' is not correct");
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
    return Substitution(std::move(result));
}

Substitution Substitution::mutate(std::size_t pos) const
{
    if(pos + 1 >= _size)
        throw std::out_of_range("Substitution::mutate: pos out of range");

    std::vector<int> result = _data;
    std::swap(result[pos], result[pos + 1]);
    return Substitution(std::move(result));
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
