#include "Player.h"
#include <iostream>

const unsigned int PLAYER_ANIMATION_COLUMNS = 6;
const unsigned int PLAYER_ANIMATION_ROWS = 3;
const float PLAYER_ANIMATION_SWITCH_TIME = 0.2f;

const unsigned int ATTACKING_ANIMATION_COLUMNS = 6;
const unsigned int ATTACKING_ANIMATION_ROWS = 1;
const float ATTACKING_ANIMATION_SWITCH_TIME = 0.1f;

const float JUMP_HEIGHT = 400.f;
const float GRAVITY = 981.f;
const float JUMP_SPEED = -sqrtf(2.f * GRAVITY * JUMP_HEIGHT);

const float HITBOX_WIDTH = 85.f;
const float HITBOX_HEIGHT = 80.f;

const float WIDTH_AUX = 2.2f;
const float HEIGHT_AUX = 1.9f;

const sf::Vector2f AUX_VECTOR = sf::Vector2f(46.f, 66.f);


Player::Player(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize,
	std::string pathToTexture, std::string textureName, float speed, long int hp, int numPlayer) :
	Character(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName, speed, hp)
{
	this->initVariables();

	this->numPlayer = numPlayer;

	if (this->numPlayer == 1)
		this->attackingTexture = this->graphicsManager->loadTextures("images/player_attacking.png", "PLAYER_ATTACKING");
	if (this->numPlayer == 2)
		this->attackingTexture = this->graphicsManager->loadTextures("images/player2_attacking.png", "PLAYER_2_ATTACKING");

	this->initAnimation(PLAYER_ANIMATION_COLUMNS, PLAYER_ANIMATION_ROWS, PLAYER_ANIMATION_SWITCH_TIME);
	this->initAttackingAnimation();
}

Player::Player() :
	Character()
{
	this->isSlow = false;
	this->canJump = false;
	this->isJumping = false;
	this->attacking = false;
	this->animationRow = PLAYER_IDLE;
	this->swordHitbox = nullptr;
	this->attackingTexture = nullptr;
	this->attackingAnimation = nullptr;
	this->inCastle = false;
}

Player::~Player()
{
	this->attackingTexture = nullptr;

	delete this->animation;
	delete this->attackingAnimation;

	if (this->swordHitbox)
		delete this->swordHitbox;
}

void Player::initAttackingAnimation()
{
	this->attackingAnimation = new AnimationManager();
	this->attackingAnimation->setImageCount(sf::Vector2u(ATTACKING_ANIMATION_COLUMNS, ATTACKING_ANIMATION_ROWS));
	this->attackingAnimation->setSwitchTime(ATTACKING_ANIMATION_SWITCH_TIME);
	this->attackingAnimation->setUVRect(this->attackingTexture);
}

void Player::initVariables()
{
	this->isSlow = false;
	this->canJump = false;
	this->isJumping = false;
	this->attacking = false;
	this->animationRow = PLAYER_IDLE;
	this->swordHitbox = nullptr;
	this->inCastle = false;
}

// Verifica constantemente várias ações que são necessárias para o bom funcionamento do player
void Player::update()
{
	this->updateMovementInput();
	this->updateAnimationRow();
	this->updatePositions();
	this->updateSprite();
	this->isJumping = !this->canJump;
}

// Verifica se o jogador apertou alguma tecla que movimenta o personagem
void Player::updateMovementInput()
{
	this->velocity.x = 0.f;

	if (this->numPlayer == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			this->move(1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			this->move(-1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
			this->attacking = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->canJump)
			this->jump();
	}
	if (this->numPlayer == 2) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			this->move(1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			this->move(-1.f);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			this->attacking = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && this->canJump)
			this->jump();
	}


	this->updateVariables();


	this->body.move(this->velocity * (*this->dt));
}

void Player::updateVariables()
{
	if (this->velocity.y == JUMP_SPEED)
		this->isJumping = true;

	if (this->attacking)
		this->velocity.x = 0.f;

	this->velocity.y += 2.f * this->gravity * (*this->dt);

	if (!this->isSlow)
		this->speed = 250.f;
}

void Player::updateAnimationRow()
{
	if (this->isJumping)
		this->animationRow = PLAYER_JUMPING;
	else if (this->velocity.x == 0)
		this->animationRow = PLAYER_IDLE;
	else
		this->animationRow = PLAYER_RUNNING;
}

void Player::updatePositions()
{
	this->position = this->body.getPosition();

	if (!this->attacking) {
		if (this->facingRight)
			this->sprite.setPosition(sf::Vector2f(this->position.x + this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
		else
			this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (WIDTH_AUX / this->spriteScale), this->position.y + this->body.getSize().y * (HEIGHT_AUX / this->spriteScale)));
	}
	else {
		if (this->facingRight)
			this->sprite.setPosition((this->position + this->body.getSize() - AUX_VECTOR));
		else
			this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x + AUX_VECTOR.x, this->position.y + this->body.getSize().y - AUX_VECTOR.y));
	}
}

void Player::updateSprite()
{
	if (this->attacking) {
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

void Player::updateAnimation()
{
	this->sprite.setTexture(*this->texture);
	this->animation->update(this->animationRow, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}

void Player::updateAttackingAnimation()
{
	this->sprite.setTexture(*this->attackingTexture);
	this->attackingAnimation->update(0, *this->dt);
	this->sprite.setTextureRect(this->attackingAnimation->getUVRect());

	if (this->attackingAnimation->getCurrentImage().x >= ATTACKING_ANIMATION_COLUMNS - 1) {
		this->attacking = false;
		this->attackingAnimation->setCurrentImage(sf::Vector2u(0, this->attackingAnimation->getCurrentImage().y)); // reseta o frame da animação para o próximo ataque
	}
}

void Player::jump()
{
	this->canJump = false;
	this->velocity.y = JUMP_SPEED;
}