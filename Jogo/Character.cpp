#include "Character.h"

const float GRAVITY = 981.f;

Character::Character(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
	std::string pathToTexture, std::string textureName, float speed, int hp) :
	Entity(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->speed = speed;
	this->hp = hp;

	this->velocity = sf::Vector2f(0.f, 0.f);
	this->gravity = GRAVITY;
	this->facingRight = true;
}

Character::Character() :
	Entity()
{
	this->speed = 1.f;
	this->facingRight = true;
	this->gravity = GRAVITY;
	this->hp = 1000;
}

Character::~Character()
{
}

void Character::updateCollision(sf::Vector2f direction)
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

void Character::move(float dir_x)
{
	if (this->facingRight && dir_x < 0.f)
		this->flip();
	else if (!this->facingRight && dir_x > 0.f)
		this->flip();

	this->velocity.x = dir_x * this->speed;
}

void Character::flip()
{
	if (this->facingRight)
		this->sprite.setScale(-this->spriteScale, this->spriteScale);
	else
		this->sprite.setScale(this->spriteScale, this->spriteScale);

	this->facingRight = !this->facingRight;
}

bool Character::isDead()
{
	if (this->hp <= 0)
		return true;
	return false;
}
