#include "SwordAttack.h"
#include "Player.h"

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

SwordAttack::SwordAttack(sf::Vector2f position, Player* player)
{
	this->position = position;
	this->player = player;

	this->playerBody = this->player->getShape();

	this->hitbox.setPosition(this->position);
	this->hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	this->hitbox.setOrigin(this->hitbox.getSize() / 2.f);

	this->hitbox.setFillColor(sf::Color(0, 0, 0, 0));
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOutlineThickness(1.f);

	this->collider.setBody(&this->hitbox);
}

SwordAttack::~SwordAttack()
{
}

void SwordAttack::update()
{
	this->updatePosition();
	this->updateFlip();
}

void SwordAttack::updatePosition()
{
	this->hitbox.setPosition(sf::Vector2f(this->playerBody->getPosition().x + (this->playerBody->getSize().x / 1.5f), this->playerBody->getPosition().y));
}

void SwordAttack::updateFlip()
{
	if (this->player->getFacingRight())
		this->hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	else
		this->hitbox.setSize(sf::Vector2f(-HITBOX_WIDTH, HITBOX_HEIGHT));
}
