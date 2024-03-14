#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject()
	{
	}

	virtual void initialize() = 0;
	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	sf::Texture texture;
	sf::Sprite sprite;
	
};

