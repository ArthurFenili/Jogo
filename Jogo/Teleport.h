#pragma once

#include "Obstacle.h"

class Teleport : public Obstacle
{
private:
	int color;
	int phase;

public:
	Teleport(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, int phase);
	Teleport();
	~Teleport();
};
