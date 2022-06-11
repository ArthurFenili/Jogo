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

	if (id == DOOR)
		this->sprite.setPosition(sf::Vector2f(this->position.x, this->position.y + 40.f));
	else if (id == CASTLE)
		this->sprite.setPosition(sf::Vector2f(this->position.x, this->position.y + 40.f));
	else
		this->sprite.setPosition(this->position);
	this->sprite.setScale(sf::Vector2f(this->spriteScale, this->spriteScale));
	this->sprite.setOrigin(this->body.getSize() / 2.f);

	if (this->texture != nullptr)
		this->sprite.setTexture(*this->texture);

	this->animation = nullptr;

	this->body.setFillColor(sf::Color::Transparent);
	//this->body.setOutlineColor(sf::Color::Red);
	//this->body.setOutlineThickness(1.f);
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
	this->animation = nullptr;
}

void Entity::initAnimation(unsigned int columns, unsigned int rows, float switchTime)
{
	this->animation = new AnimationManager();
	this->animation->setImageCount(sf::Vector2u(columns, rows));
	this->animation->setSwitchTime(switchTime);
	this->animation->setUVRect(this->texture);
}
