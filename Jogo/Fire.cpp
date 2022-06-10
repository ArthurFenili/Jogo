#include "Fire.h"

const unsigned int FIRE_ANIMATION_COLUMNS = 6;
const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

Fire::Fire(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName) :
	Obstacle(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->initAnimation(FIRE_ANIMATION_COLUMNS, ANIMATION_ROWS, SWITCH_TIME);

	this->body.setPosition(sf::Vector2f(this->position.x, this->position.y + 64.f * 0.2f));
	this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (1.3f / this->spriteScale), this->position.y - this->body.getSize().y + 6.f));

	this->sprite.setScale(sf::Vector2f(this->spriteScale, 2.f));

	this->burningDamage = (rand() % 5) + 1;
}

Fire::Fire() :
	Obstacle()
{
	this->burningDamage = 1;
}

Fire::~Fire()
{
	delete this->animation;
}
