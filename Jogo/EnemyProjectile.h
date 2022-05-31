#pragma once
#include "Character.h"
#include "Player.h"


class EnemyProjectile :
    public Character
{
private:
	Player* player1;
	float speed;

	bool attacking;

public:
	EnemyProjectile(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale, float speed);
	EnemyProjectile();
	~EnemyProjectile();

	void setPlayer(Player* player) { this->player1 = player; }

	void move();

	void updateCollision(sf::Vector2f direction);
};

