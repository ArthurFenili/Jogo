#include "DarkKnight.h"
#include <iostream>

const float WIDTH_AUX = 0.5f;
const float HEIGHT_AUX = 0.01f;
const double HEIGHT_AUX_ATTACKING = 0.0000000000000000001f;

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

int DarkKnight::gotHit(0);

DarkKnight::DarkKnight(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp) :
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->madnessCoefficient = 0.007f;
	this->damage = 1.f;
	this->attackTimer = 0;

	this->attackingTexture = this->graphicsManager->loadTextures("images/dark_knight_attacking.png", "DARK_KNIGHT_ATTACKING");
	this->chargingTexture = this->graphicsManager->loadTextures("Images/dark_knight_charging.png", "DARK_KNIGHT_CHARGING");

	this->initAnimation(8, 1, 0.3f);
	this->initAttackingAnimation();
}

DarkKnight::DarkKnight() :
	Enemy()
{
}

DarkKnight::~DarkKnight()
{
}

void DarkKnight::initAttackingAnimation()
{
	this->attackingAnimation = new AnimationManager();
	this->attackingAnimation->setImageCount(sf::Vector2u(7, 1));
	this->attackingAnimation->setSwitchTime(0.3f);
	this->attackingAnimation->setUVRect(this->attackingTexture);
}

void DarkKnight::updateAttack()
{
	if ((this->gotHit / 175) >= 2) {
		this->damage += madnessCoefficient;
	}

	if (this->attackTimer < 2000) {
		this->attackTimer++;
	}
}

void DarkKnight::updateAttackingAnimation()
{
	this->sprite.setTexture(*this->attackingTexture);
	this->attackingAnimation->update(0, *this->dt);
	this->sprite.setTextureRect(this->attackingAnimation->getUVRect());

	if (this->attackingAnimation->getCurrentImage().x >= 7 - 1) {
		this->attackTimer = 0;
		this->attackingAnimation->setCurrentImage(sf::Vector2u(0, this->attackingAnimation->getCurrentImage().y)); // reseta o frame da animação para o próximo ataque
	}
}

void DarkKnight::update()
{
	this->updateMovement();
	if (this->attackTimer < 2000)
		this->updatePosition(WIDTH_AUX, HEIGHT_AUX);
	else if (this->attackTimer >= 2000) {
		this->updatePosition(WIDTH_AUX, HEIGHT_AUX_ATTACKING);
	}
		
	this->updateAttack();

	if (this->attackTimer >= 2000) {
		this->updateAttackingAnimation();
		this->swordHitbox = new SwordAttack(this->graphicsManager, this->dt, SWORD, 0.f, this->position, sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT), "", "NONE", this);
		this->swordHitbox->update();
	}
	else {
		this->updateAnimation();
		if (this->swordHitbox) {
			delete this->swordHitbox;
			this->swordHitbox = nullptr;
		}
	}
}

void DarkKnight::updateAnimation()
{
	if (this->attackTimer >= 1800)
		this->sprite.setTexture(*this->chargingTexture);
	else
		this->sprite.setTexture(*this->texture);
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}
