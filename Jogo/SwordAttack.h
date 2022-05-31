#pragma once

#include "Collider.h"

class Player;

class SwordAttack
{
private:
	Player* player;
	sf::Vector2f position;

	sf::RectangleShape* playerBody;
	sf::RectangleShape hitbox;

	Collider collider;
	
public:
	SwordAttack(sf::Vector2f position = sf::Vector2f(0.f, 0.f), Player* player = nullptr);
	~SwordAttack();

	Collider* getCollider() { return &this->collider; }

	sf::RectangleShape* getShape() { return &this->hitbox; }

	void update();
	void updatePosition();
	void updateFlip();
};

