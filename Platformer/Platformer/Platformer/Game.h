#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"
#include "Globals.h"
#include "Input.h"
#include "TileManager.h"

class Game
{
public:
	Game();
	void Run();

private:
	void update(float dt);
	void render();


	sf::RenderWindow window;
	sf::View view;

	Player player;

	TileManager tileman;
	std::vector<Chunk>* chunks;
};

