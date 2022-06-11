#pragma once

#include "Entity.h"
#include "Character.h"

class SwordAttack : public Entity
{
private:
	Character* user;
	sf::RectangleShape* userBody;
	
public:
	SwordAttack(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, Character* user = nullptr);
	SwordAttack();
	~SwordAttack();

	void update();
	void updatePosition();
	void updateFlip();
};

