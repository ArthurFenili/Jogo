#include "Character.h"

const float GRAVITY = 981.f;

Character::Character(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
	float* dt, float spriteScale) :
	Entity(graphicsManager, position, pathToTexture, textureName, bodySize)
{
	this->dt = dt;

	this->sprite.setPosition(this->position - this->body.getSize() / 2.f);
	this->sprite.setScale(sf::Vector2f(spriteScale, spriteScale));
	this->sprite.setOrigin(this->body.getSize() / 2.f);

	this->velocity = sf::Vector2f(0.f, 0.f);
	this->gravity = GRAVITY;
	this->facingRight = true;
}

Character::Character() :
	Entity()
{
	this->dt = nullptr;
	this->facingRight = true;
	this->gravity = GRAVITY;
}

Character::~Character()
{
}

void Character::flip()
{
	if (this->facingRight)
		this->sprite.setScale(-this->sprite.getScale().x, this->sprite.getScale().y);
	else
		this->sprite.setScale(-this->sprite.getScale().x, this->sprite.getScale().y);

	this->facingRight = !this->facingRight;
}

void Character::renderSprite()
{
	this->graphicsManager->renderSprite(&this->sprite);
}
