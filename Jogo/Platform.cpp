#include "Platform.h"

const unsigned int PORTAL_ANIMATION_COLUMNS = 8;
const unsigned int FIRE_ANIMATION_COLUMNS = 6;

const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

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
		this->body.setTexture(this->texture);
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
	this->body.setTexture(this->texture);
	this->animation->update(0, *this->dt);
	this->body.setTextureRect(this->animation->getUVRect());
}
