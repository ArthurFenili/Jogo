#include "Enemy.h"

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Enemy::Enemy(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
	std::string pathToTexture, std::string textureName, float speed, int hp) :
	Character(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->player = nullptr;
	this->initAnimation(6, 1, 0.3f);
}

Enemy::Enemy()
{
	this->player = nullptr;
	this->speed = 0.f;
}

Enemy::~Enemy()
{
	this->player = nullptr;
	delete this->animation;
}

void Enemy::update()
{
	this->updateMovement();
	this->updatePositions();
	this->updateAnimation();
}

void Enemy::updateMovement()
{
	if (this->player->getPosition().x > this->getPosition().x)
		this->move(1.f);
	if (this->player->getPosition().x < this->getPosition().x)
		this->move(-1.f);

	this->velocity.y += 2.f * this->gravity * (*this->dt);

	this->body.move(this->velocity * (*this->dt));
}

void Enemy::updatePositions()
{
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
}

void Enemy::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}
