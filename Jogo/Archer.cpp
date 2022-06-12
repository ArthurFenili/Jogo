#include "Archer.h"
#include <iostream>

const float WIDTH_AUX = 0.1f;
const float HEIGHT_AUX = 3.3f;

Archer::Archer(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp) :
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->attacking = false;
	this->shootTimer = 0;
	this->initAnimation(8, 1, 0.2f);
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
	this->updateAnimation();
}

void Archer::updateAttack()
{
	if (this->shootTimer < 500) {
		this->shootTimer++;
	}

	if ((this->shootTimer >= 500) &&
		(this->player->getPosition().x <= this->getPosition().x + 500 && this->player->getPosition().x >= this->getPosition().x - 500)) {
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

void Archer::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}