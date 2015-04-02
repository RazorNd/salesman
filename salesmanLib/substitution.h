#ifndef SUBSTITUTION_H
#define SUBSTITUTION_H

#include "objectivefunction.h"
#include <vector>
#include <ostream>

class ObjectiveFunction;

class Substitution
{
    static ObjectiveFunction _funtion;    

    const std::size_t _size;
    std::vector<int> _data;

    void randomInit();
    bool isCorrect();    
public:

    Substitution(std::size_t size);
    Substitution(std::vector<int> &data);    

    std::size_t size() const;
    std::string toString() const;


    int operator[] (std::size_t i) const;
    bool operator < (const Substitution& other) const;
    Substitution operator* (const Substitution& other) const;
    Substitution mutate (std::size_t pos) const;

    friend std::ostream &operator << (std::ostream& out, const Substitution &substitution);
    static ObjectiveFunction getFuntion();
    static void setFuntion(const ObjectiveFunction &value);
};

std::ostream &operator << (std::ostream& out, const Substitution &substitution);

#endif // SUBSTITUTION_H
