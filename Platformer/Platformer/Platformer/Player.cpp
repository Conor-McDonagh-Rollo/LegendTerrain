#include "Player.h"

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		horizontal = -1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		horizontal = 1.f;
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
			velocity.y += dt * 1000.f;
		if (sprite.getPosition().y > 500.f)
		{
			grounded = true;
			velocity.y = 0;
			sprite.setPosition(sprite.getPosition().x, 500.f);
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			velocity.y = -5.5f;
			grounded = false;
		}
	}
	

	sprite.move(velocity);
}

void Player::draw()
{
	Globals::window->draw(sprite);
}

