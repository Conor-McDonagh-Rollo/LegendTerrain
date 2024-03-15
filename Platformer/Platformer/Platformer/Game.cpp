#include "Game.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1280, 720), "SFML Game")
{
    Globals::window = &window;
    Input::SetButton("left", sf::Keyboard::A);
    Input::SetButton("right", sf::Keyboard::D);
    Input::SetButton("jump", sf::Keyboard::Space);
}

void Game::Run()
{

    sf::Clock clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // 60fps
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time maxFrameTime = sf::seconds(1.0f / 10.0f); // Cap frametime to 10fps

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;


        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
            if (ev.type == sf::Event::KeyPressed || ev.type == sf::Event::KeyReleased) {
                Input::keyState[ev.key.code] = (ev.type == sf::Event::KeyPressed);
            }
        }
        
        // Cap the frametime
        if (timeSinceLastUpdate > maxFrameTime) {
            timeSinceLastUpdate = maxFrameTime;
        }
        
        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            update(timePerFrame.asSeconds()); // Use fixed timestep
            Input::Update();
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
