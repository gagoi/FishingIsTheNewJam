#include "Fishes.hpp"

Fishes::Fishes(int seed):_background(sf::Quads, 4), _bg_rect(sf::RectangleShape(sf::Vector2f(800, seed))), _direction(false), _seed(seed)
{
    std::mt19937 gen1(seed);
    std::uniform_int_distribution<> dist_type(1, 18);
    std::uniform_int_distribution<> dist_type_stone(20, 23);
    std::normal_distribution<> dist_size(1, 0.25);
    std::uniform_int_distribution<> dist_pos_x(0, 600);
    std::uniform_int_distribution<> dist_pos_y(1000, seed);
    std::normal_distribution<> dist_speed_x(4, 2);
    std::normal_distribution<> dist_speed_y(-2.05, 0.02);
    std::uniform_int_distribution<> speed_x_dir(0, 1);

    _bg_texture.loadFromFile("./bin/textures/game_background.png");
    _bg_texture.setRepeated(true);

    // on définit la position des sommets du triangle
    _background[0].position = sf::Vector2f(0, 0);
    _background[1].position = sf::Vector2f(800, 0);
    _background[2].position = sf::Vector2f(800, seed);
    _background[3].position = sf::Vector2f(0, seed);

    // on définit la couleur des sommets du triangle
    _background[0].color = sf::Color(0, 0, 255, 0);
    _background[1].color = sf::Color(0, 0, 255, 0);
    _background[2].color = sf::Color(0, 0, 40, 255);
    _background[3].color = sf::Color(0, 0, 40, 255);

    _bg_rect.setTextureRect(sf::IntRect(0, 0, 800, seed));
    _bg_rect.setTexture(&_bg_texture);
    for (int i = 0; i < seed / 100; ++i)
    {
        int s = dist_size(gen1);
        float speed_y = dist_speed_y(gen1);
        while (speed_y < -3 || speed_y > -2)
            speed_y = dist_speed_y(gen1);
        push_front(new Fish(sf::Vector2f(dist_pos_x(gen1), dist_pos_y(gen1)), s, sf::Vector2f(speed_x_dir(gen1) == 0 ? dist_speed_x(gen1) : -dist_speed_x(gen1), speed_y), dist_type(gen1)));
    }

    for (int i = 0; i < seed / 500; ++i)
    {
        push_front(new Stone(sf::Vector2f(dist_pos_x(gen1), dist_pos_y(gen1)), dist_size(gen1), sf::Vector2f(0, -2), dist_type_stone(gen1)));
    }

    push_front(new Treasure(seed));
}

Fishes::~Fishes()
{
    std::for_each(begin(), end(), [this](Fish * pfish){delete pfish;});
}


void Fishes::update()
{
    int dt = _direction ? -5 : 2;
    _background[0].position.y -= dt;
    _background[1].position.y -= dt;
    _background[2].position.y -= dt;
    _background[3].position.y -= dt;

    _hook.move(dt);
    _bg_rect.move(sf::Vector2f(0, -dt));
    if (!_direction && (_hook.getDepth() > _seed - 100|| _hook.isHitted()))
    {
        _direction = true;
        _hook.changeDirection();
    }
    std::for_each(begin(), end(), [this](Fish * pfish){pfish->update(_hook, _direction);});
}

void Fishes::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  //  target.draw(_bg_rect);
    target.draw(_hook);
    std::for_each(begin(), end(), [this, &target](Fish * pfish){target.draw(*pfish);});
    target.draw(_background);
}