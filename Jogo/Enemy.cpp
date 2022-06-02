#include "Enemy.h"

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Enemy::Enemy(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, 
	float* dt, float spriteScale, float speed) :
	Character(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed)
{
	this->speed = speed;
	this->player1 = nullptr;

	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(6, 1));
	this->animation->setSwitchTime(0.3f);
	this->animation->setUVRect(this->texture);

	this->sprite.setTexture(*this->texture);
}

Enemy::Enemy()
{
	this->animation = nullptr;
	this->player1 = nullptr;
	this->speed = 0.f;
}

Enemy::~Enemy()
{
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
	if (this->player1->getPosition().x > this->getPosition().x)
		this->move(1.f);
	if (this->player1->getPosition().x < this->getPosition().x)
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
