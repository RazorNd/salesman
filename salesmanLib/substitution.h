#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "objectivefunction.h"
#include <vector>
#include <initializer_list>
#include <ostream>
#include <random>

class ObjectiveFunction;

class Substitution
{
    static ObjectiveFunction _funtion;
    static std::default_random_engine random;

    const std::size_t _size;
    std::vector<int> _data;

    void randomInit();
    bool isCorrect();
public:
    Substitution() = delete;

    Substitution(std::size_t size);
    Substitution(std::vector<int> &&data);
    Substitution(std::initializer_list<int> &&initList);

    std::size_t size() const;

    int operator[] (std::size_t i) const;
    bool operator < (const Substitution& other) const;
    Substitution operator* (const Substitution& other) const;

    friend std::ostream &operator << (std::ostream& out, const Substitution &substitution);
    static ObjectiveFunction getFuntion();
    static void setFuntion(const ObjectiveFunction &value);
};

std::ostream &operator << (std::ostream& out, const Substitution &substitution);

#endif // SUBSTITUTION_H
