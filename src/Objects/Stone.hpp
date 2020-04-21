#pragma once

#include "Fish.hpp"
#include <random>

class Stone : public Fish
{
private:
    static std::mt19937 gen;
    static std::uniform_int_distribution<> dist;
public:
    Stone(sf::Vector2f, double, sf::Vector2f, int);
    virtual int getType() {return 1;}
    virtual void update(Hook &, bool);
};