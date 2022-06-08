#include "Archer.h"

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Archer::Archer(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp):
	Enemy(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)

{
	this->player = nullptr;
	//this->initAnimation();

	this->attacking = false;
	shootTimer = 0;
	projectile = new Projectile();
	projectile->setUser(this);
}

Archer::Archer()
{
	this->player = nullptr;
}

Archer::~Archer()
{
	this->player = nullptr;
	//delete this->animation;
	delete this->projectile;
}

void Archer::update()
{
	this->updateMovement();
	this->updatePosition();
	this->updateAttack();
	//this->updateAnimation();
}

void Archer::updateMovement()
{
	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (this->player->getPosition().x > this->getPosition().x) {
		this->velocity.x = 1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = true;
	}
	if (this->player->getPosition().x < this->getPosition().x) {
		this->velocity.x = -1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = false;
	}

	this->body.move(this->velocity * (*this->dt));

	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);
}

void Archer::updatePosition()
{
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));

}

void Archer::updateAttack()
{
	if (shootTimer < 2000)
		shootTimer++;

	if (shootTimer >= 2000) {
		projectile->createProjectile();
		shootTimer = 0;
	}

	for (int i = 0; i < projectile->getVectorSize(); i++) {
		if (this->player->getPosition().x < this->getPosition().x)
			projectile->moveProjectile(i, -1.f);
		else if (this->player->getPosition().x > this->getPosition().x)
			projectile->moveProjectile(i, 1.f);
		projectile->verifyErase(i);
	}
}
