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
	bool isJumping;
	bool canJump;
	float jumpHeight;
	bool isSlow;
	bool attacking;

	SwordAttack* swordHitbox;

public:
	Player(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize,
		float* dt, float spriteScale, float speed);
	Player();
	~Player();

	void initAnimations();
	void initVariables();

	void update();
	void updateMovementInput();
	void updateVariables();
	void updateAnimationRow();
	void updatePositions();
	void updateSprite();
	void updateAnimation();
	void updateAttackingAnimation();

	void setCanJump(bool canJump) { this->canJump = canJump; }
	void setIsSlow(bool isSlow) { this->isSlow = isSlow; }

	SwordAttack* getSwordHitbox() { return this->swordHitbox; }

	void renderSwordHitBox_TMP() { this->graphicsManager->renderShape(this->swordHitbox->getShape()); }

	void jump();
};
