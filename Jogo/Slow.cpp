#include "Slow.h"

Slow::Slow(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName) :
	Obstacle(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
}

Slow::Slow() :
	Obstacle()
{
}

Slow::~Slow()
{
}
