#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape
{
private:
    sf::Texture _background;
    sf::Text _label;
    sf::Text _score;
    std::string _texte;
public:
    Button(int, int, int, int, int, std::string const &, sf::Font const &);
    bool contains(int x, int y);
    std::string const & getTexte() const;
    void draw(sf::RenderTarget &, sf::RenderStates) const;
};