#include "Entity.h"

Entity::Entity(GraphicsManager* graphicsManager, sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize)
{
	this->entityType = NONE;

	if (textureName == "PLAYER")
		this->entityType = PLAYER;
	else if (textureName == "SKELETON")
		this->entityType = SKELETON;
	else if (textureName == "ARCHER")
		this->entityType = ARCHER;

	this->graphicsManager = graphicsManager;
	this->position = position;

	this->texture = this->graphicsManager->loadTextures(pathToTexture, textureName);

	this->body.setPosition(this->position);
	this->body.setSize(bodySize);
	this->body.setOrigin(this->body.getSize() / 2.f);

	this->collider.setBody(&this->body);
}

Entity::Entity()
{
	this->graphicsManager = nullptr;
	this->texture = nullptr;
	this->entityType = NONE;
}

Entity::~Entity()
{
}
