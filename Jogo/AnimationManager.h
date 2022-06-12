#pragma once

#include <SFML/Graphics.hpp>

class AnimationManager
{
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	sf::IntRect uvRect;
	
	float totalTime;
	float switchTime;

public:
	AnimationManager();
	~AnimationManager();

	void update(int row, float dt);

	void setUVRect(sf::Texture* texture);
	sf::IntRect getUVRect() { return this->uvRect; }

	void setImageCount(sf::Vector2u imageCount) { this->imageCount = imageCount; }
	void setSwitchTime(float switchTime) { this->switchTime = switchTime; }

	void setCurrentImage(sf::Vector2u currentImage) { this->currentImage = currentImage; }
	sf::Vector2u getCurrentImage() { return this->currentImage; }
};
