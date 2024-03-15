#pragma once
#include "GameObject.h"
#include "Globals.h"
#include "Input.h"

class Player : public GameObject
{
private:
	sf::Vector2f velocity{ 0.f,0.f };
	bool grounded = false;
public:
	Player();
	void initialize() override;
	void update(float dt) override;
	void draw() override;
};

