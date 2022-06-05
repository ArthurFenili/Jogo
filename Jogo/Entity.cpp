#include "Entity.h"

Entity::Entity(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale)
{
	this->graphicsManager = graphicsManager;
	this->position = position;
	this->dt = dt;
	this->spriteScale = spriteScale;

	this->texture = this->graphicsManager->loadTextures(pathToTexture, textureName);

	this->body.setPosition(this->position);
	this->body.setSize(bodySize);
	this->body.setOrigin(this->body.getSize() / 2.f);

	this->collider.setBody(&this->body);

	this->body.setFillColor(sf::Color::Transparent);
	this->body.setOutlineColor(sf::Color::Red);
	this->body.setOutlineThickness(1.f);
}

Entity::Entity()
{
	this->graphicsManager = nullptr;
	this->texture = nullptr;
	this->dt = nullptr;
	this->spriteScale = 1.f;
}

Entity::~Entity()
{
}
