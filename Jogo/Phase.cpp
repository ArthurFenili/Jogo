#include "Phase.h"

Phase::Phase(GraphicsManager* graphicsManager)
{
	this->graphicsManager = graphicsManager;
}

Phase::Phase()
{
	this->graphicsManager = nullptr;
}

Phase::~Phase()
{
}

void Phase::setPlatform(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize)
{
	Platform* tmp = nullptr;
	tmp = new Platform(this->graphicsManager, position, pathToTexture, textureName, bodySize);

	this->platformList.addPlatform(tmp);
}

void Phase::setEnemy(sf::Vector2f position, std::string pathToTexture, std::string textureName, sf::Vector2f bodySize, float* dt, float spriteScale, float speed, Player* player)
{
	Enemy* tmp = nullptr;
	tmp = new Enemy(this->graphicsManager, position, pathToTexture, textureName, bodySize, dt, spriteScale, speed);
	tmp->setPlayer(player);

	this->entityList.addEntity(tmp);
}

void Phase::update()
{
	for (int i = 0; i < this->entityList.getSize(); i++) {
		this->entityList[i]->update();
		if (static_cast<Character*>(this->entityList[i])->isDead())
			this->entityList.pop(this->entityList[i]);
	}
}

void Phase::render()
{
	for (int i = 0; i < this->platformList.getSize(); i++)
		this->platformList[i]->renderShape();

	for (int i = 0; i < this->entityList.getSize(); i++)
		this->entityList[i]->renderSprite();
}
