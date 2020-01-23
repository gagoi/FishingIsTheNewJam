#include "Treasure.hpp"

Treasure::Treasure(int depth)
{
    _text_normal.loadFromFile("./bin/textures/treasure.png");
    _text_reverse.loadFromFile("./bin/textures/treasure.png");
    double sizeScaler = 0.1;
    _shape.setTexture(&_text_normal);
    _shape = sf::RectangleShape(sf::Vector2f((float) _text_normal.getSize().x * sizeScaler, (float) _text_normal.getSize().y * sizeScaler));
    _shape.setOrigin((float) _text_normal.getSize().x * sizeScaler / 2, (float) _text_normal.getSize().y * sizeScaler / 2);
    _shape.setTexture(&_text_normal);
    _speed = sf::Vector2f(0, -2);
    _catch = false;
    _uncatchable = false;
    _shape.move(sf::Vector2f(350, depth - 200));
    _value = 1000;
}