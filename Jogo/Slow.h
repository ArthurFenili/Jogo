#pragma once

#include "Obstacle.h"

class Slow : public Obstacle
{
private:
	float slowCoefficient;

public:
	Slow(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName);
	Slow();
	~Slow();

	float getSlowCoefficient() { return this->slowCoefficient; }
};
