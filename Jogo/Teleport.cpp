#include "Teleport.h"

const unsigned int TELEPORT_ANIMATION_COLUMNS = 8;
const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

const float TELEPORT_WIDTH_AUX = 0.4f;
const float TELEPORT_HEIGHT_AUX = 2.f;

Teleport::Teleport(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName) :
	Obstacle(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->initAnimation(TELEPORT_ANIMATION_COLUMNS, ANIMATION_ROWS, SWITCH_TIME);

	this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (TELEPORT_WIDTH_AUX / this->spriteScale) - 38.f, this->position.y - (this->body.getSize().y * (TELEPORT_HEIGHT_AUX / this->spriteScale))));
}

Teleport::Teleport() :
	Obstacle()
{
}

Teleport::~Teleport()
{
	delete this->animation;
}
