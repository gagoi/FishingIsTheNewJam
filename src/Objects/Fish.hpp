#pragma once 

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "Hook.hpp"

class Fish : public sf::Drawable
{
protected:
    float _value;
    bool _catch;
    bool _use_normal_text;
    sf::RectangleShape _shape;
    sf::Texture _text_reverse;
    sf::Texture _text_normal;
    sf::Vector2f _speed;
    Fish(){};
public:
    Fish(sf::Vector2f, double, sf::Vector2f, int);
    virtual void update(Hook &, bool);
    void draw(sf::RenderTarget &, sf::RenderStates) const;
    virtual int getType() {return 0;}
};