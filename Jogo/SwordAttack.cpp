#include "SwordAttack.h"
#include "Player.h"

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

SwordAttack::SwordAttack(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
	std::string pathToTexture, std::string textureName, Player* player) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->player = player;
	this->playerBody = this->player->getShape();
}

SwordAttack::SwordAttack() :
	Entity()
{
	this->player = nullptr;
	this->playerBody = nullptr;
}

SwordAttack::~SwordAttack()
{
	this->playerBody = nullptr;
	this->player = nullptr;
}

void SwordAttack::update()
{
	this->updatePosition();
	this->updateFlip();
}

void SwordAttack::updatePosition()
{
	this->body.setPosition(sf::Vector2f(this->playerBody->getPosition().x + (this->playerBody->getSize().x / 1.5f), this->playerBody->getPosition().y));
}

void SwordAttack::updateFlip()
{
	if (this->player->getFacingRight())
		this->body.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	else
		this->body.setSize(sf::Vector2f(-HITBOX_WIDTH, HITBOX_HEIGHT));
}
