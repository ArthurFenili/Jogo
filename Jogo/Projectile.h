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
    int getVectorSize() { return projectiles.size(); }
    std::vector<sf::RectangleShape*>* getVectorProjectiles() { return &projectiles; }

};

// TIRAR PROJETIL DE ENEMY PROJECTILE E CRIAR AQUI NESSA CLASSE