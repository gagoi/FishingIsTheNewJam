#include "Hook.hpp"

Hook::Hook() : _score(0), _shape(sf::RectangleShape(sf::Vector2f(100, 100))), _chain(sf::RectangleShape(sf::Vector2f(100, 400))), _accelerationAngle(0), _hit(false)
{
    _text.loadFromFile("bin/textures/hook.png", sf::IntRect(0, 0, 256, 256));
    _chain_down.loadFromFile("./bin/textures/chain_down.png");
    _chain_up.loadFromFile("./bin/textures/chain_up.png");
    //_shape.setFillColor(sf::Color::Red);
    _chain.setTexture(&_chain_down);
    _shape.setTexture(&_text);
    _shape.setPosition(400, 400);
    _chain.setPosition(420, -45);
    _shape.rotate(-45);
    _depth = 400;
}

void Hook::move(int dy)
{
    _depth += dy;
    if (_accelerationAngle != 0)
        _accelerationAngle -= _accelerationAngle < 0 ? -0.5 : 0.5;
}

void Hook::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(_shape);
    target.draw(_chain);
    /*
    sf::RectangleShape hitbox( sf::Vector2f(_shape.getGlobalBounds().width - 100, _shape.getGlobalBounds().height - 120));
    hitbox.setPosition(sf::Vector2f(_shape.getGlobalBounds().left + 50, _shape.getGlobalBounds().top + 100));
    hitbox.setFillColor(sf::Color::Red);
    target.draw(hitbox);
    */
}

void Hook::changeDirection()
{
    _chain.setTexture(&_chain_up);
}

void Hook::move(sf::Vector2f const & m)
{
    if ((m.x < 0 && _shape.getGlobalBounds().left >= 0 - 15) || (m.x > 0 && _shape.getGlobalBounds().left + _shape.getGlobalBounds().width <= 800 + 25))
    {
        _shape.move(m);
        _chain.move(m);
        if (m.x < 0 && _accelerationAngle > -80)
            _accelerationAngle -= 2;
        else if (m.x > 0 && _accelerationAngle < 80)
            _accelerationAngle += 2;
    }
}

void Hook::score(int val)
{
    _score += val;
    if (_score < 0) _score = 0;
}

 sf::FloatRect Hook::getGlobalBounds() const {
    return sf::FloatRect(_shape.getGlobalBounds().left + 50,
                         _shape.getGlobalBounds().top + 100,
                         _shape.getGlobalBounds().width - 100,
                         _shape.getGlobalBounds().height - 120);
}
