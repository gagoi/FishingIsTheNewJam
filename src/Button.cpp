#include "Button.hpp"

Button::Button(int x, int y, int w, int h, std::string const & t, sf::Font const & f) : sf::RectangleShape(sf::Vector2f(w, h)), _texte(t)
{
    setPosition(x, y);
    _background.loadFromFile("./bin/textures/button_bg.png");
    setTexture(&_background);
    _label.setFont(f);
    _label.setString(t);
    _label.setPosition(x + (getGlobalBounds().width - _label.getGlobalBounds().width) / 2,
                       y + (getGlobalBounds().height - _label.getGlobalBounds().height) / 2);
}

bool Button::contains(int x, int y)
{
    return (x >= getGlobalBounds().left && x <= getGlobalBounds().left + getGlobalBounds().width && y >= getGlobalBounds().top && y <= getGlobalBounds().top + getGlobalBounds().height);
}


std::string const & Button::getTexte() const
{
    return _texte;
}


void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(static_cast<sf::RectangleShape>(*this));
    target.draw(_label);
}    