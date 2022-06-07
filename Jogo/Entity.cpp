#include "Entity.h"

Entity::Entity(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName) :
	Ent(graphicsManager, dt, id)
{
	this->spriteScale = spriteScale;
	this->position = position;
	this->texture = this->graphicsManager->loadTextures(pathToTexture, textureName);

	this->body.setPosition(this->position);
	this->body.setSize(bodySize);
	this->body.setOrigin(this->body.getSize() / 2.f);

	this->collider.setBody(&this->body);

	this->sprite.setPosition(this->position);
	this->sprite.setScale(sf::Vector2f(this->spriteScale, this->spriteScale));
	this->sprite.setOrigin(this->body.getSize() / 2.f);

	this->animation = nullptr;

	this->sprite.setTexture(*this->texture);
}

Entity::Entity() :
	Ent()
{
	this->animation = nullptr;
	this->texture = nullptr;
	this->spriteScale = 1.f;
}

Entity::~Entity()
{
	this->texture = nullptr;
}

void Entity::initAnimation(unsigned int columns, unsigned int rows, float switchTime)
{
	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(columns, rows));
	this->animation->setSwitchTime(switchTime);
	this->animation->setUVRect(this->texture);
}
