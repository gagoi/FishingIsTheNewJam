#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Fish.hpp"

class Treasure : public Fish
{
public:
    Treasure(int);
    virtual int getType() {return 0;}
};