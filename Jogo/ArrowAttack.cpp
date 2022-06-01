#include "ArrowAttack.h"
#include "EnemyProjectile.h"

const float HITBOX_WIDTH = 15.f;
const float HITBOX_HEIGHT = 10.f;

ArrowAttack::ArrowAttack(sf::Vector2f position, EnemyProjectile* enemy)
{
	this->position = position;
	this->enemy = enemy;

	this->enemyBody = this->enemy->getShape();

	this->hitbox.setPosition(this->position);
	this->hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	this->hitbox.setOrigin(this->hitbox.getSize() / 2.f);

	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOutlineThickness(1.f);

	this->collider.setBody(&this->hitbox);
}

ArrowAttack::~ArrowAttack()
{
}

void ArrowAttack::update()
{
	this->updatePosition();
	this->updateFlip();
}

void ArrowAttack::updatePosition()
{

	this->hitbox.setPosition(sf::Vector2f(this->enemyBody->getPosition().x + (this->enemyBody->getSize().x / 2.f), this->enemyBody->getPosition().y));
	std::cout << "atacou" << std::endl;
}

void ArrowAttack::updateFlip()
{
	if (this->enemy->getFacingRight())
		this->hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
	else
		this->hitbox.setSize(sf::Vector2f(-HITBOX_WIDTH, HITBOX_HEIGHT));
}

void ArrowAttack::updateMovement() {
	sf::Vector2f direction;
	while (!(this->getCollider()->isColliding(this->enemy->getPlayer()->getCollider(), &direction))) {
		if (this->enemy->getFacingRight())
			this->hitbox.move(1.f * (this->enemy->getDT()), 0);
		else
			this->hitbox.move(-1.f * (this->enemy->getDT()), 0);
	}
	this->enemy->deleteArrow();
}
