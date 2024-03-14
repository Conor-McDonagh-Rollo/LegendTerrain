#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "Globals.h"

class Game
{
public:
	Game();
	void Run();

private:
	void update(float dt);
	void render();


	sf::RenderWindow window;

	Player player;
};

