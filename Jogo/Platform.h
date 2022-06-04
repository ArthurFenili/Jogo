#pragma once

#include "Entity.h"
#include "AnimationManager.h"

class Platform : public Entity
{
private:
	int obstacleType;
	enum type {
		NONE = 0, FIRE, SLOW, TELEPORT, DOOR, WINDOW, NO_COLLIDER
	};

	AnimationManager* animation;

public:
	Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale = 1.f);
	Platform();
	~Platform();

	int getObstacleType() { return this->obstacleType; }

	void initAnimations();
	void updateAnimation();
};
