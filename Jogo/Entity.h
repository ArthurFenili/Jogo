#pragma once

#include "GraphicsManager.h"
#include "Collider.h"
#include <iostream>

class Entity
{
private:
	int entityType;
	enum type {
		NONE = 0, PLAYER, SKELETON, ARCHER
	};
protected:
	GraphicsManager* graphicsManager;
	sf::Texture* texture;

	sf::RectangleShape body;
	sf::Vector2f position;

	Collider collider;

public:
	Entity(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize);
	Entity();
	~Entity();

	void renderShape() { this->graphicsManager->renderShape(&this->body); }
	virtual void renderSprite() {}

	sf::RectangleShape* getShape() { return &this->body; }
	sf::Vector2f getPosition() { return this->position; }
	Collider* getCollider() { return &this->collider; }

	int getEntityType() { return this->entityType; }

	virtual void update() {}
};

