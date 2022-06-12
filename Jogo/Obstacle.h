#pragma once

#include "Entity.h"

class Obstacle : public Entity
{
protected:
	int effect;

public:
	Obstacle(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName);
	Obstacle();
	~Obstacle();

	void update();
};
