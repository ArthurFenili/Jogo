#include "Platform.h"

const unsigned int PORTAL_ANIMATION_COLUMNS = 8;
const unsigned int FIRE_ANIMATION_COLUMNS = 6;

const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

const float PORTAL_WIDTH_AUX = 0.4f;
const float PORTAL_HEIGHT_AUX = 1.f;

const float FIRE_WIDTH_AUX = 0.6f;
const float FIRE_HEIGHT_AUX = 0.8f;

Platform::Platform(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale) :
	Entity(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale)
{
	this->obstacleType = NONE;
	this->animation = nullptr;

	if (textureName == "FIRE")
		this->obstacleType = FIRE;
	else if (textureName == "SLOW")
		this->obstacleType = SLOW;
	else if (textureName == "TELEPORT")
		this->obstacleType = TELEPORT;
	else if (textureName == "DOOR")
		this->obstacleType = DOOR;
	else if (textureName == "WINDOW")
		this->obstacleType = WINDOW;
	else if (textureName == "NO_COLLIDER")
		this->obstacleType = NO_COLLIDER;

	if (this->obstacleType == FIRE || this->obstacleType == TELEPORT)
		this->initAnimations();
	else
		this->sprite.setTexture(*this->texture);

	if (this->obstacleType != TELEPORT && this->obstacleType != FIRE)
		this->sprite.setPosition(this->position);
	else if (this->obstacleType == TELEPORT)
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (PORTAL_WIDTH_AUX / this->spriteScale) - 38.f, this->position.y - (this->body.getSize().y * (PORTAL_HEIGHT_AUX /this->spriteScale))));
	else {
		this->body.setPosition(sf::Vector2f(this->position.x, this->position.y + 64.f * 0.2f));
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (1.3f / this->spriteScale), this->position.y - this->body.getSize().y + 5.f));
	}
	
	if (this->obstacleType != FIRE)
		this->sprite.setScale(sf::Vector2f(this->spriteScale, this->spriteScale));
	else
		this->sprite.setScale(sf::Vector2f(this->spriteScale, 2.f));
	this->sprite.setOrigin(this->body.getSize() / 2.f);


}

Platform::Platform() :
	Entity()
{
	this->animation = nullptr;
	this->obstacleType = NONE;
}

Platform::~Platform()
{
}

void Platform::initAnimations()
{
	this->animation = new AnimationManager();

	if (this->obstacleType == FIRE)
		this->animation->setImageCount(sf::Vector2u(FIRE_ANIMATION_COLUMNS, ANIMATION_ROWS));
	else if (this->obstacleType == TELEPORT)
		this->animation->setImageCount(sf::Vector2u(PORTAL_ANIMATION_COLUMNS, ANIMATION_ROWS));

	this->animation->setSwitchTime(SWITCH_TIME);
	this->animation->setUVRect(this->texture);
}

void Platform::updateAnimation()
{
	this->sprite.setTexture(*this->texture);
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}
