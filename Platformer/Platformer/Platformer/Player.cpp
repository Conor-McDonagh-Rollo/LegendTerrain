#include "Player.h"
#include <iostream>

Player::Player()
	: GameObject()
{
	initialize();
}

void Player::initialize()
{
	texture.loadFromFile("ASSETS//IMAGES//player.png");
	sprite.setTexture(texture);
}

void Player::update(float dt)
{
	float horizontal = 0.f;
	if (Input::GetButton("left"))
		horizontal = -5.f;
	if (Input::GetButton("right"))
		horizontal = 5.f;
	if (horizontal != 0)
	{
		velocity.x = horizontal;
	}
	else
	{
		velocity.x *= dt;
	}

	if (!grounded)
	{
		if (velocity.y < 9.f)
			velocity.y += dt * 100.f;
		if (sprite.getPosition().y > 500.f)
		{
			grounded = true;
			velocity.y = 0;
			sprite.setPosition(sprite.getPosition().x, 500.f);
		}
	}
	else
	{
		if (Input::GetButtonDown("jump"))
		{
			velocity.y = -20.f;
			grounded = false;
		}
	}
	

	sprite.move(velocity);
}

void Player::draw()
{
	Globals::window->draw(sprite);
}

