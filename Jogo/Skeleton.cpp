#include "Skeleton.h"

const unsigned int SKELETON_ANIMATION_COLUMNS = 6;
const unsigned int SKELETON_ANIMATION_ROWS = 1;
const float SKELETON_ANIMATION_SWITCH_TIME = 0.3f;

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Skeleton::Skeleton(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp):
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->player = nullptr;
	this->initAnimation(SKELETON_ANIMATION_COLUMNS, SKELETON_ANIMATION_ROWS, SKELETON_ANIMATION_SWITCH_TIME);

}

Skeleton::Skeleton()
{
	this->player = nullptr;
}

Skeleton::~Skeleton()
{
	this->player = nullptr;
	delete this->animation;
}

void Skeleton::update()
{
	this->updateMovement();
	this->updatePositions();
	this->updateAnimation();
}

void Skeleton::updateMovement()
{
	if (this->player->getPosition().x > this->getPosition().x)
		this->move(1.f);
	else if (this->player->getPosition().x < this->getPosition().x)
		this->move(-1.f);

	this->velocity.y += 2.f * this->gravity * (*this->dt);

	this->body.move(this->velocity * (*this->dt));
}

void Skeleton::updatePositions()
{
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));

}
