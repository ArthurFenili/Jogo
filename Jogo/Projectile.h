#pragma once

#include "Entity.h"

class Archer;

class Projectile : public Entity
{
private:
    Archer* archer;

public:
    Projectile(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, Archer* archer);
    Projectile();
    ~Projectile();

    void createProjectile();
    void moveProjectile(float direction);
    bool verifyErase();
};
