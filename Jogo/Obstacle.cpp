#include "Obstacle.h"

Obstacle::Obstacle(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize,
	std::string pathToTexture, std::string textureName) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
}

Obstacle::Obstacle() :
	Entity()
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}