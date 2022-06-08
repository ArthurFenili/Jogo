#pragma once

#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include<vector>
#include<SFML/Graphics.hpp>

class Archer :
	public Enemy
{
private:
    bool attacking;
    int shootTimer;
    Projectile* projectile;

public:
    Archer(GraphicsManager* graphicsManager, float* dt, int id,
        float spriteScale, sf::Vector2f position, sf::Vector2f bodySize,
        std::string pathToTexture, std::string textureName, float speed,
        long int hp);
    Archer();
    ~Archer();

    const float& getDT() { return *this->dt; }
    bool getAttacking() { return this->attacking; }

    std::vector<sf::RectangleShape*>* getVectorProjectiles() { return projectile->getVectorProjectiles(); }

    void update();
    void updateMovement();
    void updatePosition();
    void updateAttack();
};

