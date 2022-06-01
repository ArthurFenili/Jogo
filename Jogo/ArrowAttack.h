#pragma once

#include "Collider.h"
class EnemyProjectile;

class ArrowAttack
{
private:
	EnemyProjectile* enemy;
	sf::Vector2f position;

	sf::RectangleShape* enemyBody;
	sf::RectangleShape hitbox;

	Collider collider;

public:
	ArrowAttack(sf::Vector2f position = sf::Vector2f(0.f, 0.f), EnemyProjectile* enemy = nullptr);
	~ArrowAttack();

	Collider* getCollider() { return &this->collider; }

	sf::RectangleShape* getShape() { return &this->hitbox; }

	void update();
	void updatePosition();
	void updateFlip();
	void updateMovement();
};

