#include "pch.h"
#include "Bat.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pong");
    Bat bat;
    Ball ball(bat, {{ 0.f, 0.f }, { 1920.f, 1080.f }});
    bool isBallActive = false;

    sf::Font font;
    font.loadFromFile("fonts/DS-DIGI.ttf");
    sf::Text uiScore;
    int i = 0;
    uiScore.setFont(font);
    uiScore.setCharacterSize(40);
    uiScore.setFillColor(sf::Color::White);
 /*   Utils::SetOrigin(uiScore, Origins::MC);
    uiScore.setPosition(1920 / 2, 1080 / 2);*/

    InputMgr::Init();
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();
        InputMgr::Clear();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputMgr::UpdateEvent(event);
        }

        InputMgr::GetMousePos();
        InputMgr::Update(dt);
        bat.Update(dt);

        if (!isBallActive && InputMgr::GetKeyDown(sf::Keyboard::Space))
        {
            ball.fire({-1.f , 1.f } , -500.f);
            isBallActive = true;
        }

        if (!isBallActive)
        {
            ball.shape.setPosition(bat.shape.getPosition());
        }

        ball.Update(dt);

        if (ball.isDead)
        {
            isBallActive = false;
            i = 0;
            ball.fire({ 0.f ,0.f }, 0.f);
        }
        else if (ball.isBoundBat)
        {
            ball.isBoundBat = false;
            i += 100;
        }


        window.clear();
        uiScore.setString("Score : " + std::to_string(i));
        bat.Draw(window);
        ball.Draw(window);
        window.draw(uiScore);

        window.display();
        
    }

    return 0;
}