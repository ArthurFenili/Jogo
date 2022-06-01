#pragma once

#include <iostream>
#include "GraphicsManager.h"
#include "Collider.h"

class Entity
{
protected:
	GraphicsManager* graphicsManager;

	Collider collider;

	sf::Texture* texture;
	sf::RectangleShape body;

	sf::Vector2f position;

public:
	Entity(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	Entity();
	~Entity();

	Collider* getCollider() { return &this->collider; }

	sf::RectangleShape* getShape() { return &this->body; }
	sf::Vector2f getPosition() { return this->position; }
};

