#pragma once

#include "Entity.h"

class Character : public Entity
{
protected:
	float speed;
	float hp;
	float gravity;
	bool facingRight;
	
	sf::Vector2f velocity;

public:
	Character(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp);
	Character();
	~Character();

	virtual void update() {}

	void updateCollision(sf::Vector2f direction);

	void move(float dir_x);
	void flip();

	bool isDead() { return this->hp <= 0.f ? true : false; }

	void setSpeed(float speed) { this->speed = speed; }
	float getSpeed() { return this->speed; }

	void setHp(float hp) { this->hp = hp; }
	void loseHp(float damage) { this->hp -= damage; }
	float getHP() { return this->hp; }

	bool getFacingRight() { return this->facingRight; }
};
