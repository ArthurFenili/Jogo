#pragma once

#include "Player.h"

class Enemy : public Character
{
protected:
	Player* player;

public:
	Enemy(GraphicsManager* graphicsManager, float* dt, int id, 
		float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, 
		std::string pathToTexture, std::string textureName, float speed, 
		long int hp);
	Enemy();
	~Enemy();

	virtual void update();
	virtual void updateMovement();
	virtual void updatePositions();
	virtual void updateAnimation();

	void setPlayer(Player* player) { this->player = player; }
	Player* getPlayer() { return this->player; }
};
