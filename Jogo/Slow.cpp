#include "Slow.h"

Slow::Slow(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName) :
	Obstacle(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	int tmp = rand() % 3;

	if (tmp == 0)
		this->slowCoefficient = 0.5f;
	else if (tmp == 1)
		this->slowCoefficient = 0.4f;
	else if (tmp == 2)
		this->slowCoefficient = 0.3f;
}

Slow::Slow() :
	Obstacle()
{
	this->slowCoefficient = 0.5f;
}

Slow::~Slow()
{
}
