#include <SFML/Graphics.hpp>
#include "Hook.hpp"
#include "Objects/Fish.hpp"
#include "Fishes.hpp"
#include "Button.hpp"
#include "Logger.hpp"

int play_game(int lvl, sf::RenderWindow &, sf::Font &);
int menu(sf::RenderWindow &, sf::Font &);
void show_score(int, sf::RenderWindow &, sf::Font &);

int main()
{
    Logger logger;
    sf::RenderWindow window(sf::VideoMode(800, 1200), "SFML works!");
    sf::Font font;
    window.setFramerateLimit(120);
    font.loadFromFile("./bin/fonts/Adonay.ttf");
    while (true)
    {
        int lvl = menu(window, font);
        int score = play_game(lvl, window, font);
        logger[std::to_string(lvl)] = std::max(score, logger[std::to_string(lvl)]);
        logger.save();
        show_score(score, window, font);
    }
    return 0;
}

int menu(sf::RenderWindow & window, sf::Font & font)
{
    std::vector<Button*> buttons;
    sf::Texture bg;
    sf::RectangleShape background(sf::Vector2f(800, 1200));
    bg.loadFromFile("./bin/textures/background.png");
    background.setTexture(&bg);

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            buttons.push_back(new Button(i * 110 + 400 - 220, j * 110 + 400 - 220, 100, 100, std::to_string(i + j * 4 + 1), font));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Q)
                    exit(0);
            if (event.type == sf::Event::MouseButtonPressed)
                for (auto&& b : buttons)
                    if (b->contains(event.mouseButton.x, event.mouseButton.y))
                        return std::stoi(b->getTexte());
        }
        
        window.clear();
        window.draw(background);
        for (auto&& b : buttons)
            window.draw(*b);
        window.display();
    }
    exit(0);
    return 8;
}

int play_game(int lvl, sf::RenderWindow & window, sf::Font & font)
{
    Fishes f(lvl*1200 + 3000);
    sf::Text score;
    score.setFont(font);
    score.setFillColor(sf::Color::Red);
    score.setCharacterSize(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::Q)
                    exit(0);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            f.getHook().move(sf::Vector2f(-5, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            f.getHook().move(sf::Vector2f(5, 0));

        float depth = (float) f.getHook().getDepth() / 100;
        std::string depth_str = depth > 10 ? std::to_string(depth).substr(0, 5) : '0' + std::to_string(depth).substr(0, 4);
        score.setString("Score : " + std::to_string(f.getHook().getScore()) + " - Depth : " + depth_str + "m");
        f.update();

        if (depth < 0)
            return f.getHook().getScore();


        window.clear();
        window.draw(f);
        window.draw(score);
        window.display();
    }
    return 0;
}

void show_score(int score, sf::RenderWindow & window, sf::Font & font)
{
    sf::Text scoreTexte;
    sf::Texture bg;
    sf::RectangleShape background(sf::Vector2f(800, 1200));
    bg.loadFromFile("./bin/textures/background.png");
    background.setTexture(&bg);
    scoreTexte.setFont(font);
    scoreTexte.setFillColor(sf::Color::Red);
    scoreTexte.setCharacterSize(30);
    scoreTexte.setString(L"Félicitations vous avez fait un score de " + std::to_wstring(score) + L".");
    
    scoreTexte.setPosition(400 - scoreTexte.getGlobalBounds().width / 2, 500 - scoreTexte.getGlobalBounds().height / 2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Q)
                    exit(0);
                else if (event.key.code == sf::Keyboard::Enter)
                    return;
            }
        }

        window.clear();
        window.draw(background);
        window.draw(scoreTexte);
        window.display();
    }
}