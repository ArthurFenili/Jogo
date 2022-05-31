#pragma once

#include "AnimationManager.h"
#include "SwordAttack.h"
#include "Character.h"

class Player : public Character
{
private:
	enum Rows
	{
		PLAYER_IDLE = 0, PLAYER_RUNNING, PLAYER_JUMPING
	};

	int animationRow;
	AnimationManager* animation;
	AnimationManager* attackingAnimation;
	sf::Texture* attackingTexture;
	float speed;
	bool isJumping;
	bool canJump;
	float jumpHeight;

	bool attacking;

	SwordAttack swordHitbox;

public:
	Player(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale, float speed);
	Player();
	~Player();

	void initAnimations();
	void initVariables();

	void update();
	void updateMovementInput();
	void updateAnimationRow();
	void updatePositions();
	void updateSprite();
	void updateAnimation();
	void updateAttackingAnimation();
	void updateCollision(sf::Vector2f direction);

	void renderSwordHitBox_TMP();

	void move(float dir_x);
	void jump();
};
