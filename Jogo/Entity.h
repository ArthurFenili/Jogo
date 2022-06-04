#pragma once

#include "GraphicsManager.h"
#include "Collider.h"

class Entity
{
protected:
	GraphicsManager* graphicsManager;
	sf::Texture* texture;

	sf::Sprite sprite;
	sf::RectangleShape body;
	sf::Vector2f position;

	Collider collider;

	float* dt;

public:
	Entity(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale);
	Entity();
	~Entity();

	void renderShape() { this->graphicsManager->renderShape(&this->body); }
	virtual void renderSprite() {}

	sf::RectangleShape* getShape() { return &this->body; }
	sf::Vector2f getPosition() { return this->position; }
	Collider* getCollider() { return &this->collider; }

	virtual void update() {}
};

