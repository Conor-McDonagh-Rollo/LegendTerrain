#include "Player.h"
#include <algorithm>
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
	sprite.setPosition(500, 500);
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

	
	for (Chunk& c : tileman->getSurroundingChunks(sprite.getPosition().x, sprite.getPosition().y))
	{
		for (Tile& t : c.tiles)
		{
			handleCollision(t);
			if (isOnTopOfTile(t)) {
				grounded = true;
			}
			else
			{
				grounded = false;
			}
		}
	}

	if (!grounded)
	{
		if (velocity.y < 9.f)
			velocity.y += dt * 100.f;
		
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

void Player::handleCollision(Tile& tile)
{
	if (tile.getType() == tile.AIR)
		return;
	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	sf::FloatRect tileBounds = tile.body.getGlobalBounds();
	sf::FloatRect intersection;

	if (playerBounds.intersects(tileBounds, intersection)) {
		float xOverlap = intersection.width;
		float yOverlap = intersection.height;

		// Vertical Collision (head bumping or landing)
		if (xOverlap > yOverlap) {
			if (velocity.y > 0.0f) { // Moving downwards
				sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - yOverlap);
				velocity.y = 0.0f;
				grounded = true;
			}
			else if (velocity.y < 0.0f) { // Moving upwards (head bump)
				sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + yOverlap);
				velocity.y = 0.0f; // stop upward movement
			}
		}
		// Horizontal Collision (walls)
		else {
			if (velocity.x > 0.0f) { // Moving right
				sprite.setPosition(sprite.getPosition().x - xOverlap, sprite.getPosition().y);
				//wall sliding
				if (!grounded) velocity.y = std::min(velocity.y, maxSlideSpeed);
			}
			else if (velocity.x < 0.0f) { // Moving left
				sprite.setPosition(sprite.getPosition().x + xOverlap, sprite.getPosition().y);
				// wall sliding
				if (!grounded) velocity.y = std::min(velocity.y, maxSlideSpeed);
			}
		}
	}
}

bool Player::isOnTopOfTile(const Tile& tile) {
	sf::FloatRect playerBounds = sprite.getGlobalBounds();
	sf::FloatRect tileBounds = tile.body.getGlobalBounds();

	// Check if the player's bottom is colliding with the top of the tile
	float playerBottom = playerBounds.top + playerBounds.height;
	float tileTop = tileBounds.top;

	// Optional: add a small threshold to account for floating-point inaccuracies
	float threshold = 1.0f;

	return playerBottom <= tileTop + threshold && playerBounds.top < tileTop;
}
