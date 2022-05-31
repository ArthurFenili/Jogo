#pragma once

#include "EnemyProjectile.h"

class ArrowAttack
{
private:
	EnemyProjectile* enemy;
	sf::Vector2f position;

	sf::RectangleShape* enemyBody;
	sf::RectangleShape hitbox;

	Collider collider;

public:
	ArrowAttack(sf::Vector2f position = sf::Vector2f(0.f, 0.f), Player* player = nullptr);
	~ArrowAttack();

	Collider* getCollider() { return &this->collider; }

	sf::RectangleShape* getShape() { return &this->hitbox; }

	void update();
	void updatePosition();
	void updateFlip();
};

