#pragma once
#include "Enemy.h"
#include "SwordAttack.h"

class Boss :
    public Enemy
{
private:
    Player* player;

    SwordAttack* swordHitbox;

    int attackTimer;
public:
    Boss(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string TextureName, sf::Vector2f bodySize,
        float* dt, float spriteScale, float speed);
    ~Boss();

    void setPlayer(Player* player) { this->player1 = player; }

    void update();
    void updateMovement();
    void updateAttack();
    void updatePosition();
    void updateAnimation();
};

