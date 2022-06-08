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

}

void Enemy::updatePositions()
{
}

void Enemy::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}
