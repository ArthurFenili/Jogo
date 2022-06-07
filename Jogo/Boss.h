#pragma once
#include "Enemy.h"
class Boss :
    public Enemy
{
private:
public:
    Boss(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string TextureName, sf::Vector2f bodySize,
        float* dt, float spriteScale, float speed);
    ~Boss();

    void update();
    void updateMovement();
    void updateAttack();
    void updatePosition();
    void updateAnimation();
};

