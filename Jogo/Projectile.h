#pragma once
#include "Entity.h"
#include "Character.h"

class EnemyProjectile;

class Projectile :
    public Entity
{
private:
    Character* user;

    sf::RectangleShape* projectile;
    std::vector<sf::RectangleShape*> projectiles;
public:
    Projectile();
    ~Projectile();

    void createProjectile();
    void moveProjectile(int index, float direction);
    void verifyErase(int index);
    void setUser(Character* user) { this->user = user; }
    int getVectorSize() { return (int)projectiles.size(); }
    std::vector<sf::RectangleShape*>* getVectorProjectiles() { return &projectiles; }

};