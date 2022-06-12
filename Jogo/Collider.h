#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
private:
	sf::RectangleShape* body;

public:
	Collider(sf::RectangleShape* body = nullptr);
	~Collider();

	bool isColliding(Collider* other, sf::Vector2f* direction);

	void setBody(sf::RectangleShape* body) { this->body = body; }
	void move(float dx, float dy) { this->body->move(dx, dy); }

	/* Retornam a posição e metade do tamanho do body */
	sf::Vector2f getPosition() { return this->body->getPosition(); }
	sf::Vector2f getHalfSize() { return this->body->getSize() / 2.f; }
};
