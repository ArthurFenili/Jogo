#pragma once

#include "Enemy.h"

class Skeleton : public Enemy
{
private:
	float damage;

public:
	Skeleton(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp);
	Skeleton();
	~Skeleton();

	void update();

	float getDamage() { return this->damage; }

	void updateAnimation();
};
