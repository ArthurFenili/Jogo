#pragma once
#include "Entity.h"

class EnemyProjectile;

class Projectile :
    public Entity
{
private:
    EnemyProjectile* user;

    sf::RectangleShape* projectile;
    std::vector<sf::RectangleShape*> projectiles;
public:
    Projectile();
    ~Projectile();

    void createProjectile();
    void moveProjectile(int index, float direction);
    void verifyErase(int index);
    void setUser(EnemyProjectile* user) { this->user = user; }
    int getVectorSize() { return (int)projectiles.size(); }
    std::vector<sf::RectangleShape*>* getVectorProjectiles() { return &projectiles; }

};