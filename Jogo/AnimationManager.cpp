#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
	this->currentImage = sf::Vector2u(0, 0);
	this->totalTime = 0.f;
	this->switchTime = 0.f;
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::update(int row, float dt)
{
	if (this->currentImage.y != row)
		this->currentImage.x = 0;

	this->currentImage.y = row;
	this->totalTime += dt;

	if (this->totalTime >= this->switchTime) {
		this->totalTime -= this->switchTime;
		(this->currentImage.x)++;

		if (this->currentImage.x >= this->imageCount.x)
			this->currentImage.x = 0;
	}

	this->uvRect.left = this->currentImage.x * this->uvRect.width;
	this->uvRect.top = this->currentImage.y * this->uvRect.height;
}

void AnimationManager::setUVRect(sf::Texture* texture)
{
	this->uvRect.width = texture->getSize().x / this->imageCount.x;
	this->uvRect.height = texture->getSize().y / this->imageCount.y;
}
