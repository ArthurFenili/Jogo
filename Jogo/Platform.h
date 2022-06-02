#pragma once

#include "Entity.h"

class Platform : public Entity
{
private:
	int obstacleType;
	enum type {
		NONE = 0, FIRE, SLOW, TELEPORT
	};

public:
	Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	~Platform();

	int getObstacleType() { return this->obstacleType; }
};
