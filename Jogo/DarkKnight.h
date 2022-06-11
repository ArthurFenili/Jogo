#pragma once
#include "Enemy.h"
#include "SwordAttack.h"
#include <SFML/Graphics.hpp>

class DarkKnight :
    public Enemy
{
private:
    SwordAttack* swordHitbox;
    float damage;
    float madnessCoefficient; //cada vez que o player acerta um hit, aumenta a furia e a colisão com o corpo do boss da mais dano;
    int attackTimer;

    sf::Texture* attackingTexture;
    AnimationManager* attackingAnimation;

public:
    static int gotHit;

public:
    DarkKnight(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, float speed, long int hp);
    DarkKnight();
    ~DarkKnight();

    float getDamage() { return damage; }

    void updateAttack();
    void updateAttackingAnimation();

    void update();
    void updateAnimation();

    void initAttackingAnimation();

    SwordAttack* getSwordHitbox() { return this->swordHitbox; }

    void renderSwordHitBox_TMP() { this->graphicsManager->renderShape(this->swordHitbox->getShape()); }
};