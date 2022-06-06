#pragma once

#include "Character.h"
#include "Player.h"
#include "Projectile.h"

//------
#include<vector>
#include<SFML/Graphics.hpp>


class EnemyProjectile :
    public Character
{
private:
    Player* player1;
    AnimationManager* animation;

    bool attacking;

    //------------
    int shootTimer;

    //---------------
    Projectile* projectile;

public:
    EnemyProjectile(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string TextureName, sf::Vector2f bodySize,
        float* dt, float spriteScale, float speed);
    EnemyProjectile();
    ~EnemyProjectile();
    
    void setPlayer(Player* player) { this->player1 = player; }
    Player* getPlayer() { return player1; }

    const float& getDT() { return *this->dt; }
    bool getAttacking() { return this->attacking; }

    std::vector<sf::RectangleShape*>* getVectorProjectiles() { return projectile->getVectorProjectiles(); }

    //---------------
    void update();
    void updateMovement();
    void updateAttack();
    void updatePosition();
    void updateAnimation();
};

