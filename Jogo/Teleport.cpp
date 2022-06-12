#include "Teleport.h"

const unsigned int TELEPORT_ANIMATION_COLUMNS = 8;
const unsigned int ANIMATION_ROWS = 1;
const float SWITCH_TIME = 0.2f;

const float TELEPORT_WIDTH_AUX = 0.4f;
const float TELEPORT_HEIGHT_AUX = 2.f;

Teleport::Teleport(GraphicsManager* graphicsManager, float* dt, int id, float spriteScale, sf::Vector2f position, sf::Vector2f bodySize, std::string pathToTexture, std::string textureName, int phase) :
	Obstacle(graphicsManager, dt, id, spriteScale, position, bodySize, pathToTexture, textureName)
{
	this->initAnimation(TELEPORT_ANIMATION_COLUMNS, ANIMATION_ROWS, SWITCH_TIME);

	this->phase = phase;

	// Cada instância tem uma cor aleatória

	this->color = rand() % 3;

	if (this->color == 0) {
		if (this->phase == 0)
			this->texture = this->graphicsManager->loadTextures("images/teleport_p1_yellow.png", "TELEPORT_P1_YELLOW");
		else
			this->texture = this->graphicsManager->loadTextures("images/teleport_yellow.png", "TELEPORT_YELLOW");
		this->sprite.setTexture(*this->texture);
	}
	else if (this->color == 1) {
		if (this->phase == 0)
			this->texture = this->graphicsManager->loadTextures("images/teleport_p1_red.png", "TELEPORT_P1_RED");
		else
			this->texture = this->graphicsManager->loadTextures("images/teleport_red.png", "TELEPORT_RED");
		this->sprite.setTexture(*this->texture);
	}

	this->sprite.setPosition(sf::Vector2f(this->position.x - this->body.getSize().x * (TELEPORT_WIDTH_AUX / this->spriteScale) - 38.f, this->position.y - (this->body.getSize().y * (TELEPORT_HEIGHT_AUX / this->spriteScale))));
	
}

Teleport::Teleport() :
	Obstacle()
{
	
}

Teleport::~Teleport()
{
	delete this->animation;
}
