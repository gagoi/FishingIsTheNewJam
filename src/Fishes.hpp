#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <random>
#include <algorithm>

#include "Objects/Fish.hpp"
#include "Objects/Treasure.hpp"
#include "Objects/Stone.hpp"
#include "Hook.hpp"

class Fishes : public std::list<Fish*>, public sf::Drawable
{
private:
    sf::VertexArray _background;
    sf::Texture _bg_texture;
    sf::RectangleShape _bg_rect;
    bool _direction;
    Hook _hook;
    int _seed;
public:
    Fishes(int seed);
    ~Fishes();
    void update();
    void draw(sf::RenderTarget &, sf::RenderStates) const;
    Hook & getHook() {return _hook;}
};