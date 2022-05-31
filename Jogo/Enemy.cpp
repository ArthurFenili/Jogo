#include "Enemy.h"
#include <iostream>

Enemy::Enemy(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, 
	float* dt, float spriteScale, float speed) :
	Character(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale)
{
	this->speed = speed;
	this->player1 = nullptr;
	this->sprite.setTexture(*this->texture);
	this->body.setTexture(this->texture);
	this->body.setOutlineColor(sf::Color::Red);
	this->body.setOutlineThickness(1.f);
}

Enemy::Enemy()
{
	this->player1 = nullptr;
	this->speed = 0.f;
}

Enemy::~Enemy()
{

}

void Enemy::move()
{
	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (this->player1->getPosition().x > this->getPosition().x) {
		this->velocity.x = 1.f * this->speed;
		this->body.move(this->velocity * (*this->dt));
	}
	if (this->player1->getPosition().x < this->getPosition().x) {
		this->velocity.x = -1.f * this->speed;
		this->body.move(this->velocity * (*this->dt));
	}

	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);
}

void Enemy::updateCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f)
		this->velocity.x = 0.f;
	else if (direction.x > 0.f)
		this->velocity.x = 0.f;

	if (direction.y < 0.f)
		this->velocity.y = 0.f;
	else if (direction.y > 0.f)
		this->velocity.y = 0.f;
}