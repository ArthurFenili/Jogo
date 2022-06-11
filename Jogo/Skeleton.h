#pragma once

#include "Enemy.h"

class Skeleton : public Enemy
{
private:
	int damage;

public:
	Skeleton(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp);
	Skeleton();
	~Skeleton();

	void update();

	int getDamage() { return this->damage; }

	void updateAnimation();
};
