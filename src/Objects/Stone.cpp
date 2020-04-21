#include "Stone.hpp"
std::mt19937 Stone::gen(30);

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
            if (!_catch && _shape.getGlobalBounds().intersects(hook.getGlobalBounds()))
            {
                std::uniform_int_distribution<> dist(2, 8);
                int nb_to_lost = dist(gen);

                for (int i = 0; i < nb_to_lost; ++i)
                    hook.removeRandFish();
            }
        }
    }
}
