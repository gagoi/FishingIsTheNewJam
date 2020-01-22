#include "Fish.hpp"

Fish::Fish(sf::Vector2f pos, double sizeScaler, sf::Vector2f speed, int name):
   _value(name > 16 ? (name - 16) * -50 : name * 5 + 30), _catch(false), _use_normal_text(true), _speed(speed), _uncatchable(false)
{
    if (speed.x < 0)
    {
        _text_normal.loadFromFile("./bin/textures/fishes/reverse/fishing" + std::to_string(name) + "_reverse.png");
        _text_reverse.loadFromFile("./bin/textures/fishes/normal/fishing" + std::to_string(name) + ".png");
    }
    else
    {
        _text_reverse.loadFromFile("./bin/textures/fishes/reverse/fishing" + std::to_string(name) + "_reverse.png");
        _text_normal.loadFromFile("./bin/textures/fishes/normal/fishing" + std::to_string(name) + ".png");
    }
    sizeScaler /= 248.0 / 100.0;
    _shape = sf::RectangleShape(sf::Vector2f(_text_normal.getSize().x * sizeScaler, _text_normal.getSize().y * sizeScaler));
    _shape.setOrigin(_text_normal.getSize().x * sizeScaler / 2, _text_normal.getSize().y * sizeScaler / 2);
    _shape.setTexture(&_text_normal);
    _shape.move(pos);
}

void Fish::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
    target.draw(_shape);
}

void Fish::update(Hook & hook, bool direction)
{
    if (!_catch && _shape.getGlobalBounds().intersects(hook.getGlobalBounds()) && !_uncatchable)
    {
        _shape.rotate(90);
        _shape.setPosition(sf::Vector2f(hook.getGlobalBounds().left + (hook.getGlobalBounds().width + _shape.getGlobalBounds().width) / 2, hook.getGlobalBounds().top));
        _catch = true;
        hook.score(_value);
        hook.addFish(this);
    } 
    else if (_catch)
    {
      //  _shape.setPosition(sf::Vector2f(hook.getGlobalBounds().left + hook.getGlobalBounds().width / 2 - hook.getAccellerationAngle() / 5, 
       //                                 hook.getGlobalBounds().top + hook.getGlobalBounds().height + _shape.getGlobalBounds().height / 2 - 20 + hook.getAccellerationAngle() / 5));
        auto oldOrigin = _shape.getOrigin();
        _shape.setRotation(_use_normal_text ? 90 : -90);
        _shape.setOrigin(_shape.getOrigin().x / 2, 0);
        // Mouvement effects.getGlobalBounds

        _shape.rotate(hook.getAccellerationAngle());
        _shape.setPosition(sf::Vector2f(hook.getGlobalBounds().left + hook.getGlobalBounds().width / 2 - hook.getAccellerationAngle() / 2, 
                                        hook.getGlobalBounds().top + hook.getGlobalBounds().height + 20));
        _shape.setOrigin(oldOrigin);
    } 
    else {
        if (_shape.getPosition().x <= 0)
        {
            _speed.x = -_speed.x;
            _shape.setPosition(sf::Vector2f(1, _shape.getPosition().y));
            if (_use_normal_text)
                _shape.setTexture(&_text_reverse);
            else
                _shape.setTexture(&_text_normal);
            _use_normal_text = !_use_normal_text;
        } else if (_shape.getPosition().x >= 600 + _shape.getGlobalBounds().width)
        {
            _speed.x = -_speed.x;
            _shape.setPosition(sf::Vector2f(599, _shape.getGlobalBounds().top));
            if (_use_normal_text)
                _shape.setTexture(&_text_reverse);
            else
                _shape.setTexture(&_text_normal);
            _use_normal_text = !_use_normal_text;
        }
        if (!direction)
            _shape.move(_speed);
        else
        {
            _shape.move(_speed - sf::Vector2f(0, -9));
        }
    }
}

void Fish::free()
{
    _uncatchable = true;
    _catch = false;
}