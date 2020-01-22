#include "Stone.hpp"

Stone::Stone(sf::Vector2f a, double b, sf::Vector2f c, int d) : Fish(a, b, c, d)
{ 
}


void Stone::update(Hook & hook, bool direction)
{
    if (!_catch && _shape.getGlobalBounds().intersects(hook.getGlobalBounds()))
    {
        _catch = true;
        hook.hit();
    }
    else {
        if (!direction)
            _shape.move(_speed);
        else
        {
            _shape.move(sf::Vector2f(0, 5));
        }
    }
}
