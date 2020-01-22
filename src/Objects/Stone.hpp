#pragma once

#include "Fish.hpp"

class Stone : public Fish
{
public:
    
    Stone(sf::Vector2f, double, sf::Vector2f, int);
    virtual int getType() {return 1;}
    virtual void update(Hook &, bool);
};