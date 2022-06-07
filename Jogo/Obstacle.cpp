#include "Obstacle.h"

const unsigned int TELEPORT_ANIMATION_COLUMNS = 8;
const unsigned int FIRE_ANIMATION_COLUMNS = 6;
const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

const float TELEPORT_WIDTH_AUX = 0.4f;
const float TELEPORT_HEIGHT_AUX = 1.f;

const float FIRE_WIDTH_AUX = 0.6f;
const float FIRE_HEIGHT_AUX = 0.8f;

Obstacle::Obstacle(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
	std::string pathToTexture, std::string textureName) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	if (this->id == FIRE)
		this->initAnimation(FIRE_ANIMATION_COLUMNS, ANIMATION_ROWS, SWITCH_TIME);
	else if (this->id == TELEPORT)
		this->initAnimation(TELEPORT_ANIMATION_COLUMNS, ANIMATION_ROWS, SWITCH_TIME);

	if (this->id == TELEPORT)
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (TELEPORT_WIDTH_AUX / this->spriteScale) - 38.f, this->position.y - (this->body.getSize().y * (TELEPORT_HEIGHT_AUX / this->spriteScale))));
	else if (this->id == FIRE) {
		this->body.setPosition(sf::Vector2f(this->position.x, this->position.y + 64.f * 0.2f));
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (1.3f / this->spriteScale), this->position.y - this->body.getSize().y + 5.f));
	}

	if (this->id == FIRE)
		this->sprite.setScale(sf::Vector2f(this->spriteScale, 2.f));
}

Obstacle::Obstacle() :
	Entity()
{
}

Obstacle::~Obstacle()
{
	if (this->id == TELEPORT || this->id == FIRE)
		delete this->animation;
}

void Obstacle::update()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}