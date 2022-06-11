#include "DarkKnight.h"
#include <iostream>

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

int DarkKnight::gotHit(0);

DarkKnight::DarkKnight(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp):
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->madnessCoefficient = 0.007f;
	this->damage = 1.f;
	this->attackTimer = 0;
}

DarkKnight::DarkKnight():
	Enemy()
{
}

DarkKnight::~DarkKnight()
{
}

void DarkKnight::updateAttack()
{
	if ((gotHit / 175) >= 2) {
		this->damage += madnessCoefficient;
	}

	if (this->attackTimer < 3000) {
		this->attackTimer++;
	}

	if (attackTimer >= 3000) {
		attackTimer = 0;
		//this->updateAttackingAnimation();
		this->swordHitbox = new SwordAttack(this->graphicsManager, this->dt, SWORD, 0.f, this->position, sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT), "", "NONE", this);
		this->swordHitbox->update();
	}
	else {
		//this->updateAnimation();
		if (this->swordHitbox) {
			delete this->swordHitbox;
			this->swordHitbox = nullptr;
		}
	}
}

void DarkKnight::update()
{
	this->updateMovement();
	this->updatePosition(WIDTH_AUX, HEIGHT_AUX);
	this->updateAttack();
	//this->updateAnimation();
}
