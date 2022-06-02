#pragma once

#include "Entity.h"

class Character : public Entity
{
protected:
	sf::Sprite sprite;
	sf::Vector2f velocity;

	float* dt;

	float spriteScale;
	float gravity;
	float speed;

	bool facingRight;

	int hp;

public:
	Character(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale, float speed);
	Character();
	~Character();

	void updateCollision(sf::Vector2f direction);

	void move(float dir_x);
	void flip();

	void renderSprite() { this->graphicsManager->renderSprite(&this->sprite); }

	void loseHp() { (this->hp)--; }
	bool isDead();

	bool getFacingRight() { return this->facingRight; }
};

