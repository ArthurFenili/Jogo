#include "Player.h"

const unsigned int PLAYER_ANIMATION_COLUMNS = 6;
const unsigned int PLAYER_ANIMATION_ROWS = 3;
const unsigned int ATTACKING_ANIMATION_COLUMNS = 6;
const unsigned int ATTACKING_ANIMATION_ROWS = 1;
const float PLAYER_ANIMATION_SWITCH_TIME = 0.2f;
const float ATTACKING_ANIMATION_SWITCH_TIME = 0.1f;
const float JUMP_HEIGHT = 450.f;
const float GRAVITY = 981.f;
const float JUMP_SPEED = -sqrtf(2.f * GRAVITY * JUMP_HEIGHT);
const sf::Vector2f AUX_VECTOR = sf::Vector2f(55.f, 51.f);

const float WIDTH_AUX = 2.f;
const float HEIGHT_AUX = 2.6f;

Player::Player(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
	float* dt, float spriteScale, float speed) :
	Character(graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale)
{
	this->speed = speed;
	this->attackingTexture = this->graphicsManager->loadTextures("images/player_attackingTeste.png", "PLAYER_ATTACKING");
	this->initAnimations();
	this->initVariables();
}

Player::Player() :
	Character()
{
	this->speed = 0.f;
	this->animation = nullptr;
	this->animationRow = PLAYER_IDLE;
	this->attacking = false;
	this->attackingAnimation = nullptr;
	this->attackingTexture = nullptr;
	this->canJump = false;
	this->isJumping = true;
	this->jumpHeight = JUMP_HEIGHT;
}

Player::~Player()
{
	delete this->animation;
	delete this->attackingAnimation;
}

void Player::initAnimations()
{
	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(PLAYER_ANIMATION_COLUMNS, PLAYER_ANIMATION_ROWS));
	this->animation->setSwitchTime(PLAYER_ANIMATION_SWITCH_TIME);
	this->animation->setUVRect(this->texture);

	this->attackingAnimation = new AnimationManager();
	this->attackingAnimation->setImageCount(sf::Vector2u(ATTACKING_ANIMATION_COLUMNS, ATTACKING_ANIMATION_ROWS));
	this->attackingAnimation->setSwitchTime(ATTACKING_ANIMATION_SWITCH_TIME);
	this->attackingAnimation->setUVRect(this->attackingTexture);
}

void Player::initVariables()
{
	this->animationRow = PLAYER_IDLE;
	this->jumpHeight = JUMP_HEIGHT;
	this->canJump = false;
	this->isJumping = true;
	this->attacking = false;
	this->swordHitbox = SwordAttack(this->position, this);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->move(1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->move(-1.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->attacking = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->canJump)
		this->jump();

	if (this->velocity.y == JUMP_SPEED)
		this->isJumping = true;

	if (this->attacking)
		this->velocity.x = 0.f;

	this->velocity.y += 2.f * this->gravity * (*this->dt);

	this->body.move(this->velocity * (*this->dt));
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
		this->swordHitbox.update();
	}
	else {
		this->updateAnimation();
		this->swordHitbox.getShape()->setSize(sf::Vector2f(0.f, 0.f));
	}
}

void Player::updateAnimation()
{
	this->sprite.setTexture(*texture);
	this->animation->update(this->animationRow, *this->dt);
	this->sprite.setTextureRect(this->animation->getUVRect());
}

void Player::updateAttackingAnimation()
{
	this->sprite.setTexture(*attackingTexture);
	this->attackingAnimation->update(0, *this->dt);
	this->sprite.setTextureRect(this->attackingAnimation->getUVRect());

	if (this->attackingAnimation->getCurrentImage().x >= ATTACKING_ANIMATION_COLUMNS - 1) {
		this->attacking = false;
		this->attackingAnimation->setCurrentImage(sf::Vector2u(0, this->attackingAnimation->getCurrentImage().y)); // reseta o frame da animação para o próximo ataque
	}
}

// Atualiza os valores das componentes da velocidade baseado na direção da colisão do player
void Player::updateCollision(sf::Vector2f direction)
{
	if (direction.x < 0.f)
		this->velocity.x = 0.f;
	else if (direction.x > 0.f)
		this->velocity.x = 0.f;

	if (direction.y < 0.f) {
		this->velocity.y = 0.f;
		this->canJump = true;  // Se o jogador tiver uma colisão embaixo de si mesmo, significa que ele está em um chão e pode pular
	}
	else if (direction.y > 0.f)
		this->velocity.y = 0.f;
}

void Player::renderSwordHitBox_TMP()
{
	this->graphicsManager->renderShape(this->swordHitbox.getShape());
}

void Player::move(float dir_x)
{
	if (facingRight && dir_x < 0.f)
		this->flip();
	else if (!facingRight && dir_x > 0.f)
		this->flip();

	this->velocity.x = dir_x * this->speed;
}

void Player::jump()
{
	this->canJump = false;
	this->velocity.y = JUMP_SPEED;
}