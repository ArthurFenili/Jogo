#pragma once

#include "Obstacle.h"

class Fire : public Obstacle
{
private:
	int burningDamage;

public:
	Fire(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName);
	Fire();
	~Fire();

	int getBurningDamage() { return this->burningDamage; }
};

