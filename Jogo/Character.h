#pragma once

#include "Entity.h"

class Character : public Entity
{
protected:
	sf::Vector2f velocity;

	float gravity;
	float speed;
	bool facingRight;
	int hp;

public:
	Character(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, int hp);
	Character();
	~Character();

	virtual void update() {}

	void updateCollision(sf::Vector2f direction);

	void move(float dir_x);
	void flip();

	void setSpeed(float speed) { this->speed = speed; }
	void setHp(int hp) { this->hp = hp; }

	void loseHp() { (this->hp)--; }
	bool isDead();

	bool getFacingRight() { return this->facingRight; }
};

