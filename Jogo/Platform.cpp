#include "Platform.h"

Platform::Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize) :
	Entity(graphicsManager, position, pathToTexture, textureName, bodySize)
{
	this->obstacleType = NONE;

	if (textureName == "FIRE")
		this->obstacleType = FIRE;
	else if (textureName == "SLOW")
		this->obstacleType = SLOW;
	else if (textureName == "TELEPORT")
		this->obstacleType = TELEPORT;

	this->body.setTexture(this->texture);
}

Platform::~Platform()
{
}
