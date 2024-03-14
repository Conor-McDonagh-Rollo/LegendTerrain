#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "SFML Game")
{
    Globals::window = &window;
}

void Game::Run()
{

    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // 60 frames per second
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;

        sf::Event ev;
        while (window.pollEvent(ev)) {
            
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(dt.asSeconds());
        }

        render();
    }
}

void Game::update(float dt)
{
    player.update(dt);
}

void Game::render()
{
    // Render
    window.clear();
    player.draw();
    window.display();
}
