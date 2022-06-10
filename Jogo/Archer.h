#pragma once

#include "Enemy.h"
#include "Projectile.h"
#include <vector>

class Archer : public Enemy
{
private:
	bool attacking;
	int shootTimer;

	std::vector<Projectile*> arrows;

public:
	Archer(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp);
	Archer();
	~Archer();

	void update();
	void updateAttack();

	std::vector<Projectile*>* getArrowsVector() { return &this->arrows; }

	bool getAttacking() { return this->attacking; }

	void updateAnimation();
};
