#include "Archer.h"
#include <iostream>
const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Archer::Archer(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp) :
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->attacking = false;
	this->shootTimer = 0;
}

Archer::Archer() :
	Enemy()
{
	this->attacking = false;
	this->shootTimer = 0;
}

Archer::~Archer()
{
}

void Archer::update() {
	this->updateMovement();
	this->updatePosition(WIDTH_AUX, HEIGHT_AUX);
	this->updateAttack();
}

void Archer::updateAttack()
{
	if (this->shootTimer < 80)
		(this->shootTimer)++;

	if (this->shootTimer >= 80) {
		Projectile* tmp = nullptr;
		tmp = new Projectile(this->graphicsManager, this->dt, SWORD, 1.f, this->position, sf::Vector2f(10.f, 10.f), "", "NONE", this);
		tmp->createProjectile();
		this->arrows.push_back(tmp);
		this->shootTimer = 0;
	}

	for (int i = 0; i < this->arrows.size(); i++) {
		if (this->player->getPosition().x < this->getPosition().x)
			this->arrows[i]->moveProjectile(-1.f);
		else if (this->player->getPosition().x > this->getPosition().x)
			this->arrows[i]->moveProjectile(1.f);
		if (this->arrows[i]->verifyErase())
			this->arrows.erase(this->arrows.begin() + i);
	}
}
