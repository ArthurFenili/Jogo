#include "EnemyProjectile.h"

EnemyProjectile::EnemyProjectile(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, 
	float* dt, float spriteScale, float speed):
	Character(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale)

{
	this->arrowHitbox = new ArrowAttack(this->position, this);
	this->speed = speed;
	this->player1 = nullptr;
	this->sprite.setTexture(*this->texture);
	this->body.setTexture(this->texture);
	this->body.setOutlineColor(sf::Color::Red);
	this->body.setOutlineThickness(1.f);
	this->attacking = false;
}

EnemyProjectile::EnemyProjectile()
{
	this->player1 = nullptr;
	this->speed = 0.f;
	this->arrowHitbox = nullptr;
}

EnemyProjectile::~EnemyProjectile()
{
	if (this->arrowHitbox) {
		delete this->arrowHitbox;
	}
}

void EnemyProjectile::move()
{
	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (this->player1->getPosition().x > this->getPosition().x) {
		this->velocity.x = 1.f * this->speed;
		this->body.move(this->velocity * (*this->dt));
		this->facingRight = true;
	}
	if (this->player1->getPosition().x < this->getPosition().x) {
		this->velocity.x = -1.f * this->speed;
		this->body.move(this->velocity * (*this->dt));
		this->facingRight = false;
	}

	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);
}

void EnemyProjectile::deleteArrow()
{
	if (this->arrowHitbox) {
		delete this->arrowHitbox;
		this->arrowHitbox = nullptr;
	}
}

void EnemyProjectile::update() {
	this->updateMovementInput();
	this->updatePosition();
	this->updateSprite();
}

void EnemyProjectile::updateMovementInput() {
	this->move();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
		this->attacking = true;
	}

	if (this->attacking)
		this->velocity.x = 0.f;
}

void EnemyProjectile::updatePosition() {
	this->position = this->body.getPosition();
	this->sprite.setPosition(this->position);
}

void EnemyProjectile::updateSprite() {
	if (this->attacking) {
		this->arrowHitbox->update();
	}
	else {
		this->arrowHitbox->getShape()->setSize(sf::Vector2f(0.f, 0.f));
	}
}

void EnemyProjectile::updateCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f)
		this->velocity.x = 0.f;
	else if (direction.x > 0.f)
		this->velocity.x = 0.f;

	if (direction.y < 0.f)
		this->velocity.y = 0.f;
	else if (direction.y > 0.f)
		this->velocity.y = 0.f;
}

void EnemyProjectile::renderArrowHitbox_TMP() {
	this->graphicsManager->renderShape(this->arrowHitbox->getShape());
}