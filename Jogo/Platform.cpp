#include "Platform.h"

Platform::Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize) :
	Entity(graphicsManager, position, pathToTexture, textureName, bodySize)
{
	this->body.setTexture(this->texture);
}

Platform::~Platform()
{
}
