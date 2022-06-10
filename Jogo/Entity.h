#pragma once

#include "Ent.h"
#include "Collider.h"
#include "AnimationManager.h"

class Entity : public Ent
{
protected:
	AnimationManager* animation;
	sf::Texture* texture;

	sf::Sprite sprite;
	sf::RectangleShape body;

	sf::Vector2f position;

	Collider collider;

	float spriteScale;

public:
	Entity(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName);
	Entity();
	~Entity();

	void initAnimation(unsigned int columns, unsigned int rows, float switchTime);

	virtual void update() {}	

	void renderShape() { this->graphicsManager->renderShape(&this->body); }
	void renderSprite() { this->graphicsManager->renderSprite(&this->sprite); }

	sf::RectangleShape* getShape() { return &this->body; }
	sf::Sprite* getSprite() { return &this->sprite; }

	sf::Vector2f getPosition() { return this->position; }
	Collider* getCollider() { return &this->collider; }
};

