#pragma once

#include "Entity.h"

class Character : public Entity
{
protected:
	float* dt;

	sf::Sprite sprite;

	sf::Vector2f velocity;

	bool facingRight;
	float gravity;

	float spriteScale;

public:
	Character(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale);
	Character();
	~Character();

	void flip();

	void renderSprite();

	bool getFacingRight() { return this->facingRight; }
};
