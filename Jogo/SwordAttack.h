#pragma once

#include "Collider.h"

class Player;

class SwordAttack
{
private:
	Player* player;
	sf::RectangleShape* playerBody;

	sf::RectangleShape hitbox;
	sf::Vector2f position;

	Collider collider;

public:
	SwordAttack(sf::Vector2f position = sf::Vector2f(0.f, 0.f), Player* player = nullptr);
	~SwordAttack();

	sf::RectangleShape* getShape() { return &this->hitbox; }
	Collider* getCollider() { return &this->collider; }

	void update();
	void updatePosition();
	void updateFlip();
};

