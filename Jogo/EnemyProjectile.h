#pragma once

#include "Character.h"
#include "Player.h"
#include "ArrowAttack.h"


class EnemyProjectile :
    public Character
{
private:
    Player* player1;
    AnimationManager* animation;

    bool attacking;

    ArrowAttack* arrowHitbox;
public:
    EnemyProjectile(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string TextureName, sf::Vector2f bodySize,
        float* dt, float spriteScale, float speed);
    EnemyProjectile();
    ~EnemyProjectile();
    
    void setPlayer(Player* player) { this->player1 = player; }
    Player* getPlayer() { return player1; }

    void move();

    void deleteArrow();
    const float& getDT() { return *this->dt; }
    bool getAttacking() { return this->attacking; }
    
    void update();
    void updateMovement();
    void updatePosition();
    void updateAnimation();

    void renderArrowHitbox_TMP();
};

