#include "SwordAttack.h"

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

SwordAttack::SwordAttack(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
	std::string pathToTexture, std::string textureName, Character* user) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->user = user;
	this->userBody = this->user->getShape();
}

SwordAttack::SwordAttack() :
	Entity()
{
	this->user = nullptr;
	this->userBody = nullptr;
}

SwordAttack::~SwordAttack()
{
	this->userBody = nullptr;
	this->user = nullptr;
}

void SwordAttack::update()
{
	this->updatePosition();
	this->updateFlip();
}

void SwordAttack::updatePosition()
{
	this->body.setPosition(sf::Vector2f(this->userBody->getPosition().x + (this->userBody->getSize().x / 1.5f), this->userBody->getPosition().y));
}

void SwordAttack::updateFlip()
{
	if (this->user->getFacingRight())
		this->body.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	else
		this->body.setSize(sf::Vector2f(-HITBOX_WIDTH, HITBOX_HEIGHT));
}
