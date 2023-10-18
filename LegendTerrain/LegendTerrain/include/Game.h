#ifndef GAME_H
#define GAME_H

#include "Engine.h"

class Game
{
public:
	Game();
	void run();

private:
	void processInput();
	void update(float dt);
	void render();

	GLFWwindow* window = nullptr;

	Engine* engine = nullptr;
	Sprite box = Sprite("assets/test_tex/container.jpg");

	bool left = false;
	bool right = false;
};

#endif