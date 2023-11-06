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
	Sprite box = Sprite({ 0,0,0 }, "assets/test_tex/container.jpg");
	Plane plane = Plane({0,0,-5}); // Position, Texture - both optional
	Plane plane2 = Plane({ 2,0,-5 }, "assets/test_tex/test_transparent.png");
	Terrain terrain = Terrain({ 0,0,0 }, 6);

	bool left = false;
	bool right = false;
	bool rot_left = false;
	bool rot_right = false;
};

#endif