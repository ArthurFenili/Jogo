#include "Skeleton.h"
#include <iostream>

const unsigned int SKELETON_ANIMATION_COLUMNS = 6;
const unsigned int SKELETON_ANIMATION_ROWS = 1;
const float SKELETON_ANIMATION_SWITCH_TIME = 0.3f;

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Skeleton::Skeleton(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp) :
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->initAnimation(SKELETON_ANIMATION_COLUMNS, SKELETON_ANIMATION_ROWS, SKELETON_ANIMATION_SWITCH_TIME);
	this->damage = (float) ((rand() % 5) + 1);

}

Skeleton::Skeleton() :
	Enemy()
{
}

Skeleton::~Skeleton()
{
	delete this->animation;
}

void Skeleton::update()
{
	this->updateMovement();
	this->updatePosition(WIDTH_AUX, HEIGHT_AUX);
	this->updateAnimation();
}

void Skeleton::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}