#ifndef GAME_H
#define GAME_H

#include "Engine.h"
#include <map>

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

	std::vector<Object*> terrain;
	//Object* testMesh = nullptr;

	bool left = false;
	bool right = false;
	bool forward = false;
	bool backward = false;
	bool up = false;
	bool down = false;
};

#endif