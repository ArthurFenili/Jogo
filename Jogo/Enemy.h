#pragma once

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
private:
	Player* player1;
	float speed;

public:
	Enemy(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale, float speed);
	Enemy();
	~Enemy();

	void setPlayer(Player* player) { this->player1 = player; }
	
	void move();

	void updateCollision(sf::Vector2f direction);
};
