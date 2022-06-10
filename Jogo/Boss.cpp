#include "Boss.h"

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Boss::Boss(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
	float* dt, float spriteScale, float speed):
	Enemy(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed)
{
	this->speed = speed;
	this->player = nullptr;

	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(8, 1));
	this->animation->setSwitchTime(0.3f);
	this->animation->setUVRect(this->texture);

	this->sprite.setTexture(*this->texture);

	this->body.setFillColor(sf::Color(0, 0, 0, 0));
	this->body.setOutlineColor(sf::Color::Red);
	this->body.setOutlineThickness(1.f);
}

Boss::~Boss()
{
	this->animation = nullptr;
	this->player1 = nullptr;
	this->speed = 0.f;
}

void Boss::update()
{
	this->updateMovement();
	this->updatePosition();
	this->updateAttack();
	//this->updateAnimation();
}

void Boss::updateMovement()
{
	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (this->player1->getPosition().x > this->getPosition().x) {
		this->velocity.x = 1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = true;
	}
	if (this->player1->getPosition().x < this->getPosition().x) {
		this->velocity.x = -1.f * this->speed;
		//this->body.move(this->velocity * (*this->dt));
		//this->facingRight = false;
	}

	this->body.move(this->velocity * (*this->dt));

	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);

}

void Boss::updateAttack()
{
	if (attackTimer < 2000) {
		attackTimer++;
	}

	if (this->player->getPosition().x <= this->getPosition().x + 200 &&
		this->player->getPosition().x >= this->getPosition().x - 200 &&
		attackTimer >= 2000)
	{
		attackTimer = 0;
		this->swordHitbox = new SwordAttack(this->position, this);
		std::cout << "atacou" << std::endl;
		this->swordHitbox->update();
	}
	else
	{
		if (swordHitbox) {
			delete this->swordHitbox;
			this->swordHitbox = nullptr;
		}
	}
}

void Boss::updatePosition()
{
	this->position = this->body.getPosition();

	if (this->facingRight)
		this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	else
		this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));

}

void Boss::updateAnimation()
{
	this->animation->update(0, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}
