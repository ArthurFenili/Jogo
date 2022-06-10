#pragma once

#include "Entity.h"

class Character : public Entity
{
protected:
	float speed;
	long int hp;
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

	bool isDead() { return this->hp <= 0 ? true : false; }

	void setSpeed(float speed) { this->speed = speed; }

	void setHp(long int hp) { this->hp = hp; }
	void loseHp() { (this->hp)--; }

	bool getFacingRight() { return this->facingRight; }
};
