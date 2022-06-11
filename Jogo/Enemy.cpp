#include "Enemy.h"

Enemy::Enemy(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize,
	std::string pathToTexture, std::string textureName, float speed, long int hp) :
	Character(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->player = nullptr;
}

Enemy::Enemy()
{
	this->player = nullptr;
}

Enemy::~Enemy()
{
	this->player = nullptr;
}

void Enemy::updateMovement()
{
	if (this->player->getPosition().x > this->getPosition().x)
		this->move(1.f);
	else if (this->player->getPosition().x < this->getPosition().x)
		this->move(-1.f);

	if (this->getId() == DARKKNIGHT) {
		if (this->player->getPosition().x >= 11.f * 64.f)
			this->velocity.x = 0.f;
	}

	this->velocity.y += 2.f * this->gravity * (*this->dt);

	this->body.move(this->velocity * (*this->dt));
}

void Enemy::updatePosition(float widthAux, float heightAux)
{
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (widthAux / this->spriteScale), this->position.y + this->body.getSize().y * (heightAux / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (widthAux / this->spriteScale), this->position.y + this->body.getSize().y * (heightAux / this->spriteScale)));
}