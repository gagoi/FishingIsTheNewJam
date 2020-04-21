#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "Objects/Fish.hpp"
class Fish;
class Hook : public sf::Drawable
{
private:
    static std::mt19937 gen;
    static std::uniform_int_distribution<> dist;
    int _score;
    sf::RectangleShape  _shape;
    sf::Texture _text;
    sf::Texture _chain_up, _chain_down;
    sf::RectangleShape _chain;
    int _depth;
    float _accelerationAngle;
    bool _hit;
    std::vector<Fish*> _catched_fishes;
public:
    Hook();
    void move(sf::Vector2f const &);
    void draw(sf::RenderTarget &, sf::RenderStates) const;
    void score(int);
    sf::FloatRect getGlobalBounds() const;
    int getScore() const {return _score;}
    int getDepth() const {return _depth;}
    float getAccellerationAngle() const {return _accelerationAngle;}
    void move(int);
    void changeDirection();
    void hit() {_hit = true;}
    bool isHitted() {return _hit;}
    void addFish(Fish * f);
    void removeRandFish();
};