#pragma once

#include "Entity.h"

class Player;

class SwordAttack : public Entity
{
private:
	Player* player;
	sf::RectangleShape* playerBody;
	
public:
	SwordAttack(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, Player* player = nullptr);
	SwordAttack();
	~SwordAttack();

	void update();
	void updatePosition();
	void updateFlip();
};

